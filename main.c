#include "main.h"

// Struct
// Config paths
static char *config_path[]  = {
	"configurations/windows",
	"configurations/fonts",
	"configurations/colors",
};
// Label
static char *name[] = {
	"window",
	"font",
	"color",
};
// Size
size_t size = sizeof(config_path)/sizeof(name[0]); 
Configs *configs = NULL;

/* Main func */
int main(int argc, char *argv[]) {
	// Checking is there argument when run this program
	switch(argc) {
		case 1:
			printf("Hmm, there is no arguments..\n");
			printf("See \"help\" for more details\n");
			break;
	
		default:
			// Print Help
			if(!strcmp(argv[1], "help")) {
				printHelp();
				break;
			}

			// Initialize config files
			load_configs();
			
			// Listing file
			if(!strcmp(argv[1], "list")) {
				if(argv[2]) {
					listingThem(argv, argc);	
				}
				else printf("Needed an argument\n");
				break;
			}
		
			// Selecting Configs
			else if(!strcmp(argv[1], "select")) {	// Select
				if(argv[2]) {
					//selectingThem(argv, argc);
				}
				else printf("Needed an argument\n");
				break;
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
		configs[i].config_path = config_path[i];
		configs[i].name = name[i];
		configs[i].ptr_conf = NULL;
		configs[i].length = 0;

		temp = opendir(configs[i].config_path);
		
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
	}
}

void printHelp(void) {
	char *help = "alacrittyTheme version 0.1\n"
	             "Created by Diandra\n\n"
	             "list [window,color,font]\n"
	             "select [window-cfg, color-cfg, font-cfg]\n";
	fprintf(stdout, "%s", help);
}
