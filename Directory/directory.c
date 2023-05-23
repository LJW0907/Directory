#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PEOPLE 3
#define BUFFER_SIZE 50

char** dir_names; //동적 할당 해야하므로 포인터 배열에서 이중 포인터로 변경
char** dir_emails;
char** dir_numbers;
char** dir_groups;

int n = 0;
int find_flag;
char *file_name;

void sort(char** dir_name, char** dir_call_num, int order);
int read_line(FILE *fp, char* str, int limit);
void init_directory();
void process_command();

char delim[] = "#";

int main() {
	init_directory(); //전화번호부 동적 할당 초기화
	process_command();
}

void sort(int order) { //알파벳 정렬
	char* tmp;
	int turn;

	for (int j = 0; j < order - 1; j++) {
		turn = 0;

		for (int i = 1; i < order - j; i++) {
			if (strcmp(dir_names[turn], dir_names[i]) <= 0) {
				//upper_name = dir_name[i];
				turn = i;
			}
		}

		if (turn != order - j - 1) {
			tmp = dir_names[order - j - 1];
			dir_names[order - j - 1] = dir_names[turn];
			dir_names[turn] = tmp;

			tmp = dir_numbers[order - j - 1];
			dir_numbers[order - j - 1] = dir_numbers[turn];
			dir_numbers[turn] = tmp;

			tmp = dir_emails[order - j - 1];
			dir_emails[order - j - 1] = dir_emails[turn];
			dir_emails[turn] = tmp;

			tmp = dir_groups[order - j - 1];
			dir_groups[order - j - 1] = dir_groups[turn];
			dir_groups[turn] = tmp;
		}
	}
}

int read_line(FILE *fp, char* str, int limit) { //단점을 모두 보완한 문자열 입력 함수
	int ch, i = 0;
	char tmp = ' ';

	while ((ch = fgetc(fp)) != '\n' && ch != EOF) //getchar()의 반환형은 int다!! 명심
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
	dir_emails = (char**)malloc(sizeof(char*) * MAX_PEOPLE);
	dir_groups = (char**)malloc(sizeof(char*) * MAX_PEOPLE);
}

void process_command() {
	char line[BUFFER_SIZE];
	char *command, *name, *number, *email, *group;
	char empty[] = " ";

	while (1) {
		printf("$ ");

		if (read_line(stdin, line, BUFFER_SIZE) <= 0)
			continue;

		command = strtok(line, " ");

		//command
		if (!strcmp(command, "add")) { //add

			name = _strdup(strtok(NULL, "\0"));

			if (name == NULL) {
				printf("Enter name.\n");
				continue;
			}

			printf("Phone: ");
			read_line(stdin, line, BUFFER_SIZE);
			number = _strdup(line);
			if (strlen(number) == 0)
				number = empty;

			printf("Email: ");
			read_line(stdin, line, BUFFER_SIZE);
			email = _strdup(line);
			if (strlen(email) == 0)
				email = empty;

			printf("Group: ");
			read_line(stdin, line, BUFFER_SIZE);
			group = _strdup(line);
			if (strlen(group) == 0)
				group = empty;

			if (n >= MAX_PEOPLE) { //배열이 꽉 차서 재할당
				char** tmp_names = (char**)malloc(sizeof(char*) * 2 * MAX_PEOPLE);
				char** tmp_numbers = (char**)malloc(sizeof(char*) * 2 * MAX_PEOPLE);
				char** tmp_emails = (char**)malloc(sizeof(char*) * 2 * MAX_PEOPLE);
				char** tmp_groups = (char**)malloc(sizeof(char*) * 2 * MAX_PEOPLE);

				for (int i = 0; i < n; i++) {
					tmp_names[i] = dir_names[i];
					tmp_numbers[i] = dir_numbers[i];
					tmp_emails[i] = dir_emails[i];
					tmp_groups[i] = dir_groups[i];
				}

				free(dir_names);
				free(dir_numbers);
				free(dir_emails);
				free(dir_groups);

				dir_names = tmp_names;
				dir_numbers = tmp_numbers;
				dir_emails = tmp_emails;
				dir_groups = tmp_groups;
			} //재할당 끝

			dir_names[n] = _strdup(name);
			dir_numbers[n] = _strdup(number);
			dir_emails[n] = _strdup(email);
			dir_groups[n] = _strdup(group);

			n++;

			printf("%s was added successfully\n", name);
		}

		else if (!strcmp(command, "find")) {
			find_flag = 0;
			name = strtok(NULL, delim);

			for (int i = 0; i < n; i++) {
				if (!strcmp(name, dir_names[i])) {
					printf("%s:\n", dir_names[i]);
					printf("\tPhone: %s\n", dir_numbers[i]);
					printf("\tEmail: %s\n", dir_emails[i]);
					printf("\tGroup: %s\n", dir_groups[i]);
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
					dir_emails[i] = _strdup(dir_emails[n - 1]);
					dir_groups[i] = _strdup(dir_groups[n - 1]);

					dir_names[n - 1] = NULL;
					dir_numbers[n - 1] = NULL;
					dir_emails[n - 1] = NULL;
					dir_groups[n - 1] = NULL;

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
			file_name = strtok(NULL, "\0");

			if (file_name == NULL) {
				printf("Enter file name.\n");
			}
			else if ((fp = fopen(file_name, "r"))) {
				n = 0;

				while (!(read_line(fp, line, BUFFER_SIZE)<=0)) {
					name = strtok(line, "#");
					number = strtok(NULL, "#");
					email = strtok(NULL, "#");
					group = strtok(NULL, "#");

					dir_names[n] = _strdup(name);
					dir_numbers[n] = _strdup(number);
					dir_emails[n] = _strdup(email);
					dir_groups[n] = _strdup(group);

					n++;
				}
				fclose(fp);
			}
			else
				printf("Can't read directory\n");
		}
		else if (!strcmp(command, "save")) { //save
			FILE *fp;
			file_name = strtok(NULL, "\0");

			sort(n);

			if (file_name == NULL) {
				printf("Enter save file name.\n");
			}
			else if (fp = fopen(file_name, "w")) {
				for (int i = 0; i < n; i++)
					fprintf(fp, "%s#%s#%s#%s#\n", dir_names[i], dir_numbers[i], dir_emails[i], 
						dir_groups[i]);

				fclose(fp);
			}
		}
		else if (!strcmp(command, "status")) { //status
			sort(n);

			for (int i = 0; i < n; i++) {
				printf("%s:\n", dir_names[i]);
				printf("\tPhone: %s\n", dir_numbers[i]);
				printf("\tEmail: %s\n", dir_emails[i]);
				printf("\tGroup: %s\n", dir_groups[i]);
			}
			printf("Total %d person.\n", n);
		}
		else if (!strcmp(command, "exit")) { //exit
			printf("directory close");
			exit(1);
		}
		else { //잘못된 값 입력
			printf("Enter correct system\n");

			continue;

		}
	}
}