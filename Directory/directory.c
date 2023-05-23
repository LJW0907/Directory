#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PEOPLE 3
#define BUFFER_SIZE 50

typedef struct person {
	char* name;
	char* number;
	char* email;
	char* group;
} Person;

Person* directory;

int n = 0;
int find_flag;
char *file_name;

void sort(int order);
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
			if (strcmp(directory[turn].name, directory[i].name) <= 0) {
				//upper_name = dir_name[i];
				turn = i;
			}
		}

		if (turn != order - j - 1) {
			tmp = directory[order - j - 1].name;
			directory[order - j - 1].name = directory[turn].name;
			directory[turn].name = tmp;

			tmp = directory[order - j - 1].number;
			directory[order - j - 1].number = directory[turn].number;
			directory[turn].number = tmp;

			tmp = directory[order - j - 1].email;
			directory[order - j - 1].email = directory[turn].email;
			directory[turn].email = tmp;

			tmp = directory[order - j - 1].group;
			directory[order - j - 1].group = directory[turn].group;
			directory[turn].group = tmp;
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
	directory = (Person*)malloc(sizeof(Person) * MAX_PEOPLE);
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
				directory = (Person*)realloc(directory, sizeof(Person) * 2 * MAX_PEOPLE);
			}

			directory[n].name = _strdup(name);
			directory[n].number = _strdup(number);
			directory[n].email = _strdup(email);
			directory[n].group = _strdup(group);

			n++;

			printf("%s was added successfully\n", name);
		}

		else if (!strcmp(command, "find")) {
			find_flag = 0;
			name = strtok(NULL, "\0");

			for (int i = 0; i < n; i++) {
				if (!strcmp(name, directory[i].name)) {
					printf("%s:\n", directory[i].name);
					printf("\tPhone: %s\n", directory[i].number);
					printf("\tEmail: %s\n", directory[i].email);
					printf("\tGroup: %s\n", directory[i].group);
					find_flag = 1;
					break;
				}
			}
			if (find_flag == 0)
				printf("No person named \'%s\' exists.\n", name);
		}

		else if (!strcmp(command, "delete")) {
			find_flag = 0;
			name = strtok(NULL, "\0");

			for (int i = 0; i < n; i++) {
				if (!strcmp(name, directory[i].name)) {
					directory[i].name = _strdup(directory[n-1].name);
					directory[i].number = _strdup(directory[n-1].number);
					directory[i].email = _strdup(directory[n-1].email);
					directory[i].group = _strdup(directory[n-1].group);

					directory[n - 1].name = NULL;
					directory[n - 1].number = NULL;
					directory[n - 1].email = NULL;
					directory[n - 1].group = NULL;

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

					directory[n].name = _strdup(name);
					directory[n].number = _strdup(number);
					directory[n].email = _strdup(email);
					directory[n].group = _strdup(group);

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
					fprintf(fp, "%s#%s#%s#%s#\n", directory[i].name, directory[i].number
						, directory[i].email, directory[i].group);

				fclose(fp);
			}
		}
		else if (!strcmp(command, "status")) { //status
			sort(n);

			for (int i = 0; i < n; i++) {
				printf("%s:\n", directory[i].name);
				printf("\tPhone: %s\n", directory[i].number);
				printf("\tEmail: %s\n", directory[i].email);
				printf("\tGroup: %s\n", directory[i].group);
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