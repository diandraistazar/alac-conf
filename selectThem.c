#include "main.h"

void selectThem(char **argv, int argc) {
	char *buffer = NULL;
	int len, sz_path, bytes_rd;

	// Better way
	if(argc >= 5) {
		printf("Finding started..\n");
		for(int u = 0; u < size; u++) {
	
			// Checking Is there the config?
			len = strlen(configs[u].config_path);
			for(int i = 0; i < configs[u].length; i++) {
				if(!strcmp(configs[u].ptr_conf[i].name, argv[u+2])) {
					// Open file
					sz_path = strlen(configs[u].ptr_conf[i].name) + len+1;
					buffer = realloc(buffer, sz_path);
					memset(buffer, 0, sz_path);
					sprintf(buffer, "%s/%s", configs[u].config_path, configs[u].ptr_conf[i].name);
				
					FILE *ptrFile = fopen(buffer, "r");
					if(!ptrFile)			// If fopen func return NULL, run the statement below
						continue;
					
					printf("Founded the \"%s\" config file in \"%s\"\n", argv[u+2], configs[u].config_path);
					// Read content of file
					fseek(ptrFile, 0, SEEK_END);
					bytes_rd = ftell(ptrFile);
					fseek(ptrFile, 0, SEEK_SET);
					
					// Then, store them to buffer
					configs[u].ptr_conf[i].content = malloc(bytes_rd+1);
					memset(configs[u].ptr_conf[i].content, 0, bytes_rd);
					fread(configs[u].ptr_conf[i].content, 1, bytes_rd-1, ptrFile);
					configs[u].ptr_conf[i].content[bytes_rd] = '\0';
					fclose(ptrFile);
				}
			}
		}
		// Clear memory address of buffer
		free(buffer);
	}
	// If not, run the statement below
	else {
		printf("Just %d arguments, You need %d more\n", argc-2, 3-(argc-2));
	}
	
	// Store as one complete alacritty config
	// Delete the config first
	remove(alac_conf);

	// Then, create the new one
	FILE *ptrFile = fopen(alac_conf, "a");
	if(!ptrFile) {
		perror("Can't open directory or file");
	}
	else {
		printf("\nWriting started..\n");
		for(int x = 0; x < size; x++) {
			for(int j = 0; j < configs[x].length; j++) {
				if(configs[x].ptr_conf[j].content) {
					printf("Writing \"%s\" content file to \"%s\"\n", configs[x].ptr_conf[j].name, alac_conf);
					fprintf(ptrFile, "#%s\n%s\n", configs[x].ptr_conf[j].name, configs[x].ptr_conf[j].content);
				}
			}
		}
		printf("\nSuccessfully writing config to \"%s\"\n", alac_conf);
	}

	fclose(ptrFile);
	printf("Program closed\n");

}
