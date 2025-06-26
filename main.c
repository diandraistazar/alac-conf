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
	
	if(argc == 1) {
		printf("Hmm, there is no arguments..\n");
		printf("See \"help\" for more details\n");
		return 0;
	}
	else if(!strcmp(argv[1], "help")) {
		printHelp();
	}
	
	initialize();	// Load configs
	if(!strcmp(argv[1], "list")) {
		listingThem(argv[2]);
	}

	freeAll();
	return 0;
}

/* Functions */
void initialize(void) {
	DIR *temp = NULL;
	struct dirent *file = NULL;
	
	for(int i = 0; i < size; i++) {
		temp = opendir(name[i]);
		while((file = readdir(temp))) {
			if(!strcmp(file->d_name, ".") || !strcmp(file->d_name, ".."))
				continue;

			if(i == 0) {	// Window
				window = realloc(window, sizeof(Files) * (length_win+1));
				window[length_win].name = malloc(strlen(file->d_name));
				sprintf(window[length_win].name, file->d_name);
				length_win++;
			}
			if(i == 1) {	// Color
				color = realloc(color, sizeof(Files) * (length_clr+1));
				color[length_clr].name = malloc(strlen(file->d_name));
				sprintf(color[length_clr].name, file->d_name);
				length_clr++;
			}
			if(i == 2) {	// Font
				font = realloc(font, sizeof(Files) * (length_fon+1));
				font[length_fon].name = malloc(strlen(file->d_name));
				sprintf(font[length_fon].name, file->d_name);
				length_fon++;
			}
		}
		closedir(temp);
	}
}

int listingThem(char *arg) {
	// Checking is there argument for list option
	if(arg == NULL) {
		printf("\"list\" option need an argument\n"
		       "Available Arguments: window, color, font\n");
		return -1;
	}

	Files *ptr = NULL;
	char *name = NULL;
	int len;
	if(!strcmp(arg, "window")) {
		ptr = window;
		len = length_win;
		name = "Window";
	}
	else if(!strcmp(arg, "font")) {
		ptr = font;
		len = length_fon;
		name = "Font";
	}
	else if(!strcmp(arg, "color")) {
		ptr = color;
		len = length_clr;
		name = "Color";
	}

	if(len == 0) {
		printf("Honestly, There are no %s configs available\n", name);
		return -1;
	}

	printf("%s configs:\n", name);
	for(int i = 0; i < len; i++) {
		printf("%s\n", ptr[i].name);
	}
	
	
	return 0;
}

void freeAll(void) {
	// free name and content member
	for(int i = 0; i < length_win; i++)		
		free(window[i].name);
	
	for(int i = 0; i < length_clr; i++)
		free(color[i].name);
	
	for(int i = 0; i < length_fon; i++)
		free(font[i].name);
	
	free(window);
	free(color);
	free(font);
}

void printHelp(void) {
	char *help = "alacrittyTheme version 0.1\n"
	             "Created by Diandra\n\n"
	             "list [color,font,window]\n";
	fprintf(stdout, "%s", help);
}
