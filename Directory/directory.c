#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PEOPLE 10


int return_flag(char *flag) {
	if (!strcmp(flag, "add")) {
		return 1;
	}
	else if (!strcmp(flag, "find")) {
		return 2;
	}
	else if (!strcmp(flag, "delete")) {
		return 3;
	}
	else if (!strcmp(flag, "status")) {
		return 4;
	}
	else if (!strcmp(flag, "exit")) {
		printf("directory end");
		exit(1);
	}
	else { //잘못된 값 입력
		printf("Enter correct system\n");

		while (getchar() != '\n');
		return 0;
	}
}

int main() {
	char system[8];
	int flag;

	char name[10];
	char call_num[20];

	int order = 0;
	bool find_flag = 0;
	char* dir_name[MAX_PEOPLE];
	char* dir_call_num[MAX_PEOPLE];

	while (1) {
		find_flag = 0;

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

		//flag = return_flag(system);

		//switch (flag) {
		//case 0: //잘못된 기능 입력
		//	continue;
		//case 1: //add
		//	scanf("%s", name);
		//	scanf("%s", call_num);

		//	dir_name[order] = _strdup(name);
		//	dir_call_num[order] = _strdup(call_num);
		//	order++;
	
		//	printf("%s was added successfully\n", name);
		//	break;
		//case 2: //find
		//	scanf("%s", name);

		//	for (int i = 0; i < order; i++) {
		//		if (!strcmp(name, dir_name[i])) {
		//			printf("%s\n", dir_call_num[i]);
		//			find_flag = 1;
		//			break;
		//		}
		//	}
		//	if (find_flag == 0)
		//		printf("No person named \'%s\' exists.\n", name);
		//	break;
		//case 3: //delete
		//	scanf("%s", name);

		//	for (int i = 0; i < order; i++) {
		//		if (!strcmp(name, dir_name[i])) {
		//			dir_name[i] = _strdup(dir_name[order-1]);
		//			dir_call_num[i] = _strdup(dir_call_num[order-1]);

		//			dir_name[order - 1] = NULL;
		//			dir_call_num[order - 1] = NULL;

		//			order--;
		//			find_flag = 1;

		//			printf("%s was deleted successfully.\n", name);
		//			break;
		//		}
		//	}
		//	if (find_flag == 0)
		//		printf("No person named \'%s\' exists.\n", name);
		//	break;
		//case 4: //status
		//	for (int i = 0; i < order; i++) {
		//		printf("%s %s\n", dir_name[i], dir_call_num[i]);
		//	}
		//	printf("Total %d person.\n", order);
		//	break;
		//}
	}
}