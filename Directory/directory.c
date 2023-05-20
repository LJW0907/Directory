#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PEOPLE 10

void sort(char** dir_name, char** dir_call_num, int order) { //알파벳 정렬
	char* tmp;
	int turn;

	for (int j = 0; j < order - 1; j++) {
		turn = 0;

		for (int i = 1; i < order - j; i++) {
			if (strcmp(dir_name[turn], dir_name[i]) <= 0) {
				//upper_name = dir_name[i];
				turn = i;
			}
		}

		if (turn != order - j - 1) {
			tmp = dir_name[order - j - 1];
			dir_name[order - j - 1] = dir_name[turn];
			dir_name[turn] = tmp;

			tmp = dir_call_num[order - j - 1];
			dir_call_num[order - j - 1] = dir_call_num[turn];
			dir_call_num[turn] = tmp;
		}
	}

}

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
		else if (!strcmp(system, "read")) { //read
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

				fclose(fp);
			}
			else
				printf("Can't read directory\n");
		
		}
		else if (!strcmp(system, "save")) { //save
			FILE *fp;
			scanf("%s", file_name);

			sort(dir_name, dir_call_num, order);

			if (fp = fopen(file_name, "w")) {
				for (int i = 0; i < order; i++)
					fprintf(fp, "%s %s\n", dir_name[i], dir_call_num[i]);

				fclose(fp);
			}
			else {
				printf("Can't save directory\n");
			}
		}
		else if (!strcmp(system, "status")) {
			sort(dir_name, dir_call_num, order);

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