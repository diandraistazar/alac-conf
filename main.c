#include "main.h"
#include "config.h"

size_t size = sizeof(config_name)/sizeof(config_name[0]);
Configs *configs = NULL;
size_t total_configs;

/* Main func */
int main(int argc, char *argv[]) {
	// Checking is there argument when run this program
	if(argc == 1) {
		printf("Hmm, there is no arguments..\n");
		printf("See \"help\" for more details\n");
		return 0;
	}
	else {
		// Print Help
		if(!strcmp(argv[1], "help")) {
			printHelp();
			return 0;
		}

		// Initialize config files
		load_configs();

		// Listing file
		if(!strcmp(argv[1], "list")) {
			if(argv[2]) listThem(argv, argc);	
			else printf("Needed an argument\n");
		}

		// Selecting Configs
		else if(!strcmp(argv[1], "select")) {
			if(argv[2]) selectThem(argv, argc);
			else printf("Needed an argument\n");
		}

		else if(!strcmp(argv[1], "reload")) {
			reloadThem();
		}

		// Invalid Option Argument
		else printf("There is no \"%s\" option argument\nSee \"help\" for available options\n", argv[1]);
	}
	
	// Free Memory
	freeAll();
	return 0;
}

/* Functions */
void load_configs(void) {
	
	DIR *temp				= NULL;
	struct dirent *file	= NULL;
	configs					= realloc(configs, sizeof(Configs) * size);		// Create block memory for configs
	int sz_conf, sz_d_name;
	
	for(int i = 0; i < size; i++) {
		// Create path
		configs[i].config_path = malloc(strlen(config_path) + strlen(config_name[i]) + 1);
		sprintf(configs[i].config_path, "%s/%s", config_path, config_name[i]);

		configs[i].name = config_name[i];
		configs[i].ptr_conf = NULL;
		configs[i].length = 0;

		temp = opendir(configs[i].config_path);
		
		if(!temp) {
			perror("Can't open config directory");
			freeAll();
			exit(EXIT_FAILURE);
		}

		while((file = readdir(temp))) {
			if(!strcmp(file->d_name, ".") || !strcmp(file->d_name, ".."))
				continue;
			
			sz_conf = configs[i].length;
			sz_d_name = strlen(file->d_name)+1;

			configs[i].ptr_conf = realloc(configs[i].ptr_conf, sizeof(Files) * (sz_conf+1));;
			configs[i].ptr_conf[sz_conf].name = malloc(sz_d_name);
			configs[i].ptr_conf[sz_conf].content = NULL;
			configs[i].length += 1;
			sprintf(configs[i].ptr_conf[sz_conf].name, file->d_name);
			
			total_configs+=1;
		}

		closedir(temp);
		free(file);
	}
}

void freeAll(void) {
	for(int x = 0; x < size; x++) {
		for(int j = 0; j < configs[x].length; j++) {
			free(configs[x].ptr_conf[j].name);
			free(configs[x].ptr_conf[j].content);
		}
		free(configs[x].config_path);
	}
}

void printHelp(void) {
	char *help = "alac-conf version 0.8\n"
	             "Created by Diandra\n\n"
	             "list [config_name / all]            # List available configs\n"
	             "select [conf1, conf2, conf3, ..]    # Select specific configs to use\n"
	             "reload                              # Reload Alacritty config after changes (in config_path)\n";
	fprintf(stdout, "%s", help);
}
