#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// Structure
typedef struct {
	char *name;		// Store name of file
	char *content; // Store content of file
} Files;

typedef struct {
	char *name;
	Files *ptr_conf;
	int length;
	char *config_path;
} Configs;

extern Configs *configs;
extern size_t size;

// Function Prototypes
void load_configs(void);
void freeAll(void);
void printHelp(void);
void prntList(Files *strc);
void listingThem(char **argv, int argc);
void selectingThem(char **argv, int argc);
