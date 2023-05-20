#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PEOPLE 10

int main() {
	char system[8];
	int flag;

	char name[10];
	char call_num[20];

	char file_name[20];

	int order = 0;
	bool find_flag = 0;
	char* dir_name[MAX_PEOPLE];
	char* dir_call_num[MAX_PEOPLE];


	while (1) {
		printf("& ");		
		scanf("%s", system);

		if (!strcmp(system, "add")) {
			scanf("%s", name);
			scanf("%s", call_num);

			dir_name[order] = _strdup(name);
			dir_call_num[order] = _strdup(call_num);
			order++;

			printf("%s was added successfully\n", name);
		}

		else if (!strcmp(system, "find")) {
			find_flag = 0;	
			scanf("%s", name);

			for (int i = 0; i < order; i++) {
				if (!strcmp(name, dir_name[i])) {
					printf("%s\n", dir_call_num[i]);
					find_flag = 1;
					break;
				}
			}
			if (find_flag == 0)
				printf("No person named \'%s\' exists.\n", name);
		}

		else if (!strcmp(system, "delete")) {
			find_flag = 0;
			scanf("%s", name);

			for (int i = 0; i < order; i++) {
				if (!strcmp(name, dir_name[i])) {
					dir_name[i] = _strdup(dir_name[order - 1]);
					dir_call_num[i] = _strdup(dir_call_num[order - 1]);

					dir_name[order - 1] = NULL;
					dir_call_num[order - 1] = NULL;

					order--;
					find_flag = 1;

					printf("%s was deleted successfully.\n", name);
					break;
				}
			}
			if (find_flag == 0)
					printf("No person named \'%s\' exists.\n", name);
		}
		else if (!strcmp(system, "read")) {
			FILE *fp;

			scanf("%s", file_name);

			if (fp = fopen(file_name, "r")) {
				rewind(fp);
				order = 0;

				while (!feof(fp)) {
					fscanf(fp, "%s %s\n", name, call_num);

					dir_name[order] = _strdup(name);
					dir_call_num[order] = _strdup(call_num);

					order++;
				}
			}
			else
				printf("Can't read directory\n");
			
			fclose(fp);
		}
		else if (!strcmp(system, "save")) {
			FILE *fp;

			scanf("%s", file_name);

			if (fp = fopen(file_name, "w")) {
				for (int i = 0; i < order; i++)
					fprintf(fp, "%s %s\n", dir_name[i], dir_call_num[i]);
			}
			else {
				printf("Can't save directory\n");
			}

			fclose(fp);
		}
		else if (!strcmp(system, "status")) {
			for (int i = 0; i < order; i++) {
				printf("%s %s\n", dir_name[i], dir_call_num[i]);
			}
			printf("Total %d person.\n", order);
		}
		else if (!strcmp(system, "exit")) {
			printf("directory close");
			exit(1);
		}
		else { //잘못된 값 입력
			printf("Enter correct system\n");

			while (getchar() != '\n');
			continue;
		}
	}
}