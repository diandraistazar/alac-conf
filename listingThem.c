#include "main.h"

void listingThem(char **argv, int argc) {
	int isThere;

	if(!strcmp(argv[2], "all")) {
		printf("All:\ntotal = %ld\n", total_configs);
		for(int x = 0; x < size; x++) {
			printf("\n%s configs:\n", configs[x].name);
			for(int j = 0; j < configs[x].length; j++)
				printf("- %s\n", configs[x].ptr_conf[j].name);
		}
		return;
	}

	for(int x = 0; x < size; x++) {
		if(!strcmp(argv[2], configs[x].name)) {
			printf("%s configs:\n", configs[x].name);
			for(int i = 0; i < configs[x].length; i++)
				printf("- %s\n", configs[x].ptr_conf[i].name);

			isThere = 1;
			return;
		}
		isThere = 0;
	}

	if(!isThere) {
		printf("Invalid \"%s\" option\n", argv[2]);
		return;
	}
}
