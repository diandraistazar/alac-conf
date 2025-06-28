#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// Structure
typedef struct {
	char *name;		// Store name of file
	char *content; // Store content of file
} Files;

// Enum
enum which {
	window_e,
	color_e,
	font_e,
	all_e,
};

// Function Prototypes
void initialize(void);
void freeAll(void);
void printHelp(void);
void prntList(Files *strc);
void listingThem(enum which Opt);
void selectingThem(char **argv, int argc);
