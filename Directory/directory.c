#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PEOPLE 1
#define BUFFER_SIZE 50

char** dir_names; //동적 할당 해야하므로 포인터 배열에서 이중 포인터로 변경
char** dir_numbers;

int n = 0;
int find_flag;
char *file_name;

void sort(char** dir_name, char** dir_call_num, int order);
int read_line(char* str, int limit);
void init_directory();
void process_command();

char delim[] = " ";

int main() {
	init_directory(); //전화번호부 동적 할당 초기화
	process_command();
}

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

int read_line(char* str, int limit) { //단점을 모두 보완한 문자열 입력 함수
	int ch, i = 0;
	char tmp = ' ';

	while ((ch = getchar()) != '\n') //getchar()의 반환형은 int다!! 명심
		if (i < limit-1) {
			if (tmp != ' ' || ch != ' ') {
				str[i++] = tmp = ch;
			}
		}

	if (str[i - 1] == ' ')
		i--;

	str[i] = '\0';
	return i; //문자열 길이 반환
}

void init_directory() {
	dir_names = (char**)malloc(sizeof(char*) * MAX_PEOPLE);
	dir_numbers = (char**)malloc(sizeof(char*) * MAX_PEOPLE);
}

void process_command() {
	char line[BUFFER_SIZE];
	char *command, *name, *number;
	char f_name[20], f_number[20];

	while (1) {
		printf("$ ");

		if (read_line(line, BUFFER_SIZE) <= 0)
			continue;

		command = strtok(line, delim);

		//command
		if (!strcmp(command, "add")) { //add
			name = strtok(NULL, delim);
			if (name == NULL) {
				printf("Enter name.\n");
				continue;
			}

			number = strtok(NULL, delim);
			if (number == NULL) {
				printf("Enter number.\n");
				continue;
			}

			if (n >= MAX_PEOPLE) { //배열이 꽉 차서 재할당
				int i;

				char** tmp_names = (char**)malloc(sizeof(char*) * 2 * MAX_PEOPLE);
				char** tmp_numbers = (char**)malloc(sizeof(char*) * 2 * MAX_PEOPLE);

				for (int i = 0; i < n; i++) {
					tmp_names[i] = dir_names[i];
					tmp_numbers[i] = dir_numbers[i];
				}

				free(dir_names);
				free(dir_numbers);

				dir_names = tmp_names;
				dir_numbers = tmp_numbers;
			} //재할당 끝

			dir_names[n] = _strdup(name);
			dir_numbers[n] = _strdup(number);
			n++;

			printf("%s was added successfully\n", name);
		}

		else if (!strcmp(command, "find")) {
			find_flag = 0;
			name = strtok(NULL, delim);

			for (int i = 0; i < n; i++) {
				if (!strcmp(name, dir_names[i])) {
					printf("%s\n", dir_numbers[i]);
					find_flag = 1;
					break;
				}
			}
			if (find_flag == 0)
				printf("No person named \'%s\' exists.\n", name);
		}

		else if (!strcmp(command, "delete")) {
			find_flag = 0;
			name = strtok(NULL, delim);

			for (int i = 0; i < n; i++) {
				if (!strcmp(name, dir_names[i])) {
					dir_names[i] = _strdup(dir_names[n - 1]);
					dir_numbers[i] = _strdup(dir_numbers[n - 1]);

					dir_names[n - 1] = NULL;
					dir_numbers[n - 1] = NULL;

					n--;
					find_flag = 1;

					printf("%s was deleted successfully.\n", name);
					break;
				}
			}
			if (find_flag == 0)
				printf("No person named \'%s\' exists.\n", name);
		}
		else if (!strcmp(command, "read")) { //read
			FILE *fp;
			file_name = strtok(NULL, delim);

			if (file_name == NULL) {
				printf("Enter file name.\n");
			}
			else if ((fp = fopen(file_name, "r"))) {
				n = 0;

				while (!feof(fp)) {
					fscanf(fp, "%s %s\n", f_name, f_number);

					dir_names[n] = _strdup(f_name);
					dir_numbers[n] = _strdup(f_number);

					n++;
				}
				fclose(fp);
			}
			else
				printf("Can't read directory\n");
		}
		else if (!strcmp(command, "save")) { //save
			FILE *fp;
			file_name = strtok(NULL, delim);

			sort(dir_names, dir_numbers, n);

			if (file_name == NULL) {
				printf("Enter save file name.\n");
			}
			else if (fp = fopen(file_name, "w")) {
				for (int i = 0; i < n; i++)
					fprintf(fp, "%s %s\n", dir_names[i], dir_numbers[i]);

				fclose(fp);
			}
		}
		else if (!strcmp(command, "status")) {
			sort(dir_names, dir_numbers, n);

			for (int i = 0; i < n; i++) {
				printf("%s %s\n", dir_names[i], dir_numbers[i]);
			}
			printf("Total %d person.\n", n);
		}
		else if (!strcmp(command, "exit")) {
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