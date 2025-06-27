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
};

// Function Prototypes
void initialize(void);
void freeAll(void);
void printHelp(void);
void prntList(Files *strc);
void whatIsCurrent(void);
int listingThem(enum which Opt);
int selectingThem(enum which Opt);
