#include "main.h"

void reloadMyConfig() {
	// Size of fake arguments
	int sz_arg = 5, sz_temp, index = 0, index_tmp = 2;
	char **fake_args = NULL, buffer[80], *temp = NULL;

	// Check the config first
	FILE *ptrFile = fopen(alac_conf, "r");
	if(!ptrFile) {
		perror("Where is the config?: ");
		return;
	}

	// Parse
	fake_args = (char **)malloc(sizeof(fake_args) * sz_arg);
	
	printf("Current Configs:\n");
	while(fgets(buffer, sizeof(buffer), ptrFile)) {
		if(buffer[0] == '#') {
			temp = buffer+1;
			sz_temp = strlen(temp);
			temp[sz_temp-1] = 0;
			fake_args[index_tmp] = malloc(sz_temp);
			sprintf(fake_args[index_tmp], temp);
			printf("%s -> %s\n", configs[index].name, fake_args[index_tmp]);
			index_tmp++;
			index++;

		}
	}
	
	// Call selectThem
	printf("\nReloading Started..\n\n");
	selectThem(fake_args, sz_arg);
	
	// Program Closed
	fclose(ptrFile);
	
	// Free memory
	while(2 < index_tmp--) {
		free(fake_args[index_tmp]);
	}
	free(fake_args);
	printf("\nReloaded successfully\n");
}
