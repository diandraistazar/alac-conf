#include "main.h"

Files *window = NULL;
Files *color = NULL;
Files *font = NULL;
char *name[] = {
		"configurations/windows",		// window configs
		"configurations/colors",		// color configs
		"configurations/fonts",			// font configs
};
size_t size = sizeof(name)/sizeof(name[0]);
int length_win = 0, length_clr = 0, length_fon = 0;

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
			initialize();

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
					selectingThem(argv);
				}
				else printf("Needed an argument\n");
				break;
			}
		
			// Invalid Option Argument
			else printf("There is no \"%s\" option argument\nSee \"help\" for available options\n", argv[1]);
	}

	freeAll();	// Free memory
	return 0;
}

/* Functions */
void initialize(void) {
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

int listingThem(enum which Opt) {
	Files *ptr = NULL;
	char *name = NULL;
	int len;
	switch(Opt) {
		case window_e:
			ptr = window;
			len = length_win;
			name = "Window";
			break;
		case font_e:
			ptr = font;
			len = length_fon;
			name = "Font";
			break;
		case color_e:
			ptr = color;
			len = length_clr;
			name = "Color";
			break;
	}

	// Checking
	if(len == 0 && name) {
		printf("Honestly, There are no \"%s\" configs available\n", name);
		return -1;
	}

	// Do it
	printf("%s configs:\n", name);
	for(int i = 0; i < len; i++) printf("- %s\n", ptr[i].name);
	return 0;
}

int selectingThem(char **argv) {
	// user argument
	char *buffer[size];
	int index = 0;
	for(int x = 2; x < size+2; x++) {
		if(argv[x]) {
			buffer[x-2] = argv[x];
			index++;
			continue;
		}
		break;
	}
	
	// selecting
	return 0;
}

int isConfigAvail(char *buffer) {
	Files *ptr = NULL;
	char *path = NULL;
	int len, status = 0;
	for(int x = 0; x < size; x++) {
		switch(x) {
			case window_e:
				ptr = window;
				len = length_win;
				path = name[window_e];
				break;
			case font_e:
				ptr = font;
				len = length_fon;
				path = name[font_e];
				break;
			case color_e:
				ptr = color;
				len = length_clr;
				path = name[color_e];
				break;
		}
		
		for(int j = 0; j < len; j++) {
			if(!strcmp(buffer, ptr[j].name) && !status) {
				printf("Found \"%s\" config file in \"%s\"\n", buffer, path);
				status = 1;
				return 0;
			}
		}

		if(!status)
			printf("\"%s\" config file not found in \"%s\"\n", buffer, path);
	}
	return 1;
}

void freeAll(void) {
	// free name and content member
	while(length_fon--) free(font[length_fon].name);
	while(length_win--) free(window[length_win].name);
	while(length_clr--) free(color[length_clr].name);
	free(window), free(color), free(font);
}

void printHelp(void) {
	char *help = "alacrittyTheme version 0.1\n"
	             "Created by Diandra\n\n"
	             "list [color,font,window]\n"
	             "current\n";
	fprintf(stdout, "%s", help);
}
