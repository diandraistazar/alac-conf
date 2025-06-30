#include "main.h"

void listingThem(char **argv, int argc) {
	for(int x = 0; x < (argc-2); x++) {
		for(int j = 0; j < size; j++) {
			if(!strcmp(argv[x+2], configs[j].name)) {
				printf("%s configs:\n", configs[j].name);
				for(int i = 0; i < configs[j].length; i++) {
					printf("%d %s\n", i, configs[j].ptr_conf[i].name);
				}
				break;
			}
		}
	}
}
