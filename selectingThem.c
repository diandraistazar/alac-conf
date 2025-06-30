#include "main.h"

void selectingThem(char **argv, int argc) {
	Files *ptr = NULL, **configs = malloc(sizeof(Files)+(size+10));
	char *buffer = NULL, *path = NULL;
	int len;

	if(argc >= 5) {
		printf("Finding started..\n");
		for(int x = 0; x < (argc-2); x++) {
			switch(x) {
				case window_e:
					ptr = window;
					path = name[window_e];
					len = length_win;
					break;
				case color_e:
					ptr = color;
					path = name[color_e];
					len = length_clr;
					break;
				case font_e:
					ptr = font;
					path = name[font_e];
					len = length_fon;
					break;
				}
	
				// Checking Is there the config?
				int len_name = strlen(name[x]);
				for(int i = 0; i < len; i++) {
					if(!strcmp(ptr[i].name, argv[x+2])) {
						// Open file
						int sz_path = strlen(ptr[i].name) + len_name+1;
						char toPath[sz_path];
						memset(toPath, 0, sz_path);
						strcat(toPath, name[x]), strcat(toPath, "/"), strcat(toPath, ptr[i].name);
					
						FILE *ptrFile = fopen(toPath, "r");
						if(!ptrFile)			// If fopen func return NULL, run the statement below
							continue;
						printf("Founded the \"%s\" config file in \"%s\"\n", argv[x+2], path);
						
						// Read content of file
						fseek(ptrFile, 0, SEEK_END);
						int bytes_rd = ftell(ptrFile);
						fseek(ptrFile, 0, SEEK_SET);
					
						// Then, store them to buffer
						ptr[i].content = malloc(bytes_rd+1);
						memset(ptr[i].content, 0, bytes_rd);
						fread(ptr[i].content, 1, bytes_rd-1, ptrFile);
						ptr[i].content[bytes_rd] = '\0';
						fclose(ptrFile);
					
						// Load
						switch(x) {
							case window_e:
								configs[window_e] = &ptr[i];
								break;
							case color_e:
								configs[color_e] = &ptr[i];
								break;
							case font_e:
								configs[font_e] = &ptr[i];
								break;
						}
					}
				}
		}
		
		// Store as one complete alacritty config 
		FILE *ptrFile = fopen(config_path, "w");
		if(!ptrFile) {
			perror("Can't open directory or file");
		}
		else {
			// Setting buffer size
			len = 0;
			ptr = NULL;
			for(int x = 0; x < size; x++) {
				len += strlen(configs[x]->name) + strlen(configs[x]->content)+3;	// +3 for # and \n
			}
			
			printf("\nAllocated memory as buffer..\n");
			buffer = malloc(len);		// allocation memory
			memset(buffer, 0, len);		// Clear memory
			char temp[len];				// Temp
			
			printf("\nWriting started..\n");
			for(int x = 0; x < size; x++) {
				printf("Writing \"%s\" content to buffer\n", configs[x]->name);
				sprintf(temp, "#%s\n"
				              "%s\n\n",
				              configs[x]->name, configs[x]->content);
				strcat(buffer, temp);
			}

			printf("Writing to %s\n", config_path);
			if(fwrite(buffer, len, sizeof(char), ptrFile) == len) {	// Write buffer to alacritty.toml
				printf("Success to write config\n");
			}
			else
				perror("Failed to write config");
			
			fclose(ptrFile);
			free(buffer);
			printf("Program closed\n");
		}
	}
	else {
		printf("Just %d arguments, You need %d more\n", argc-2, 3-(argc-2));
	}
}
