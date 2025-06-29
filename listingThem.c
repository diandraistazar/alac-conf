#include "main.h"

void listingThem(enum which Opt) {
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
		case all_e:
			break;
	}

	// Checking
	if(len == 0 && name) {
		printf("Honestly, There are no \"%s\" configs available\n", name);
	}
	else {
		// Do it
		printf("%s configs:\n", name);
		for(int i = 0; i < len; i++) printf("- %s\n", ptr[i].name);
	}
}
