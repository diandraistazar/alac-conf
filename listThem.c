#include "main.h"

void listThem(char **argv, int argc) {
	int isThere;
	
	// List All configs
	if(!strcmp(argv[2], "all")) {
		printf("All (total = %ld)\n", total_configs);
		for(int x = 0; x < size; x++) {
			printf("\n%s configs:\n", configs[x].name);
			for(int j = 0; j < configs[x].length; j++)
				printf("%d - %s\n", j+1, configs[x].ptr_conf[j].name);
		}
		return;
	}
	
	// List specific config
	for(int x = 0; x < size; x++) {
		if(!strcmp(argv[2], configs[x].name)) {
			printf("%s configs:\n", configs[x].name);
			for(int i = 0; i < configs[x].length; i++)
				printf("%d - %s\n", i+1, configs[x].ptr_conf[i].name);

			isThere = 1;
			return;
		}
		isThere = 0;
	}
	
	// Invalid Option
	if(!isThere) {
		printf("Invalid \"%s\" option\n", argv[2]);
		return;
	}
}
