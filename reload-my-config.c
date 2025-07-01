#include "main.h"

void reloadMyConfig(void) {
	// Size of fake arguments
	int sz_arg = 5;
	char *fake_arg[sz_arg];
	
	// Check the config first
	FILE *ptrFile = fopen(alac_conf, "r");
	if(!ptrFile) {
		perror("Where is the config?: ");
		return;
	}

	

	// Call selectingThem
	selectingThem(fake_arg, sz_arg);
}
