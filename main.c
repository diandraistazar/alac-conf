#include "main.h"

Files *window = NULL, *color = NULL, *font = NULL;
int length_win = 0, length_clr = 0, length_fon = 0;
char *config_path = "/home/diandra/.config/alacritty/alacritty.toml";
char *name[] = {
		"configurations/windows",		// window configs
		"configurations/colors",		// color configs
		"configurations/fonts",			// font configs
};
size_t size = sizeof(name)/sizeof(name[0]);

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
					if(!strcmp(argv[2], "window")) listingThem(window_e);
					else if(!strcmp(argv[2], "color")) listingThem(color_e);
					else if(!strcmp(argv[2], "font")) listingThem(font_e);
					else printf("There is no \"%s\" argument\n", argv[2]);
				}
				else printf("Needed an argument\n");
				break;
			}
		
			// Selecting Configs
			else if(!strcmp(argv[1], "select")) {	// Select
				if(argv[2]) {
					selectingThem(argv, argc);
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
	
	DIR *temp = NULL;
	struct dirent *file = NULL;
	Files *ptr = NULL;
	int *len;
	
	for(int i = 0; i < size; i++) {
		temp = opendir(name[i]);
		
		// Init
		switch(i) {
			case window_e:
				ptr = window;
				len = &length_win;
				break;
			case color_e:
				ptr = color;
				len = &length_clr;
				break;
			case font_e:
				ptr = font;
				len = &length_fon;
				break;
		}
		
		// Do it
		while((file = readdir(temp))) {
			if(!strcmp(file->d_name, ".") || !strcmp(file->d_name, ".."))
				continue;

			ptr = realloc(ptr, sizeof(Files) * (*len+1));
			ptr[*len].name = malloc(strlen(file->d_name));
			sprintf(ptr[*len].name, file->d_name);
			*len = *len + 1;
		}

		// Clear memory and copy ptr to struct Files
		switch(i) {
			case window_e:
				free(window);
				window = ptr;
				break;
			case color_e:
				free(color);
				color = ptr;
				break;
			case font_e:
				free(font);
				font = ptr;
				break;
		}
		// Free memory
		closedir(temp);
		free(file);
	}
}

void freeAll(void) {
	// free name and content member
	while(length_win--) {
		free(window[length_win].name);
		free(window[length_win].content);
	}
	while(length_fon--) {
		free(font[length_fon].name);
		free(font[length_fon].content);
	}
	while(length_clr--) {
		free(color[length_clr].name);
		free(color[length_clr].content);
	}
	free(window), free(color), free(font);
}

void printHelp(void) {
	char *help = "alacrittyTheme version 0.1\n"
	             "Created by Diandra\n\n"
	             "list [window,color,font]\n"
	             "select [window-cfg, color-cfg, font-cfg]\n";
	fprintf(stdout, "%s", help);
}
