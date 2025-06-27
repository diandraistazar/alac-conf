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
		return -1;
	}
	else if(!strcmp(argv[1], "help")) {
		printHelp();
	}
	
	initialize();	// Load configs
	
	
	if(!strcmp(argv[1], "list")) {	// Listing
		if(argv[2]) {

		if(!strcmp(argv[2], "window"))
			listingThem(window_e);

		else if(!strcmp(argv[2], "color"))
			listingThem(color_e);
		
		else if(!strcmp(argv[2], "font"))
			listingThem(font_e);
		}
		else {
			printf("Needed an argument\n");
		}
	}
	
	//else if(!strcmp(argv[1], "current")) {	// Current configs
	//	whatIsCurrent()
	//}
	
	else if(!strcmp(argv[1], "select")) {	// Select
		if(argv[2]) {	

		if(!strcmp(argv[2], "window"))
			selectingThem(window_e);

		else if(!strcmp(argv[2], "color"))
			selectingThem(color_e);

		else if(!strcmp(argv[2], "font"))
			selectingThem(font_e);
		}
		else {
			printf("Needed an argument\n");
		}
	}

	else {
		printf("There is no \"%s\" option argument\nSee \"help\" for available options\n", argv[1]);
	}

	freeAll();	// Free memory
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

void whatIsCurrent(void) {
}

int listingThem(enum which Opt) {
	Files *ptr = NULL;
	char *name = NULL;
	int len;
	if(Opt == window_e) {
		ptr = window;
		len = length_win;
		name = "Window";
	}
	else if(Opt == font_e) {
		ptr = font;
		len = length_fon;
		name = "Font";
	}
	else if(Opt == color_e) {
		ptr = color;
		len = length_clr;
		name = "Color";
	}

	// Checking
	if(len == 0 && name) {
		printf("Honestly, There are no \"%s\" configs available\n", name);
		return -1;
	}

	// Do it
	printf("%s configs:\n", name);
	for(int i = 0; i < len; i++) {
		printf("- %s\n", ptr[i].name);
	}
	
	return 0;
}

int selectingThem(enum which Opt) {
}

void freeAll(void) {
	// free name and content member
	while(length_fon--) free(font[length_fon].name);
	while(length_win--) free(window[length_win].name);
	while(length_clr--) free(color[length_clr].name);

	free(window);
	free(color);
	free(font);
}

void printHelp(void) {
	char *help = "alacrittyTheme version 0.1\n"
	             "Created by Diandra\n\n"
	             "list [color,font,window]\n"
	             "current\n";
	fprintf(stdout, "%s", help);
}
