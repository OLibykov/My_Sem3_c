#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void file_work (FILE *s1, int mode1, int mode2, int mode3);
int from_str_to_unsint(char *str);

int main (int argc, char **argv){
	int x, count = 1, mode1 = 0, mode2 = 10, mode3 = 1;
	char c;
	char *s;
	FILE *s1;
	if ((argc < 2) || (argc > 5)){
		printf("Неверное количество параметров\n");
		return 0;
	}
	s = argv[count];
	if ((s[0] == '-') && (s[1] == 's')){
		mode1 = 1;
		count++;
		s = argv[count];
	}
	x = from_str_to_unsint(s + 1);
	if ((s[0] == '-') && (x != -1)){
		mode2 = x;
		count++;
		if (count > argc){
			printf("Неверное количество параметров\n");
			return 0;
		}
		s = argv[count];
	}
	x = from_str_to_unsint(s + 1);
	if ((s[0] == '+') && (x != -1)){
		mode3 = x;
		count++;
		if (count > argc){
			printf("Неверное количество параметров\n");
			return 0;
		}
		s = argv[count];
	}
	if (count + 1 != argc){
		printf("Неверное количество параметров\n");
		return 0;
	}
	s1 = fopen(argv[count], "r");
	if (s1 == NULL){
		perror("Ошибка чтения файла\n");
		return 0;
	}
	file_work(s1, mode1, mode2, mode3);
	fclose(s1);
	return 0;
}

void file_work(FILE *s1, int mode1, int mode2, int mode3){
	int ok = 0;
	char c, q;
	int count;
	if (mode3 != 1){
		for (int i = 1; i < mode3; i++){
			c = fgetc(s1);
			while ((feof(s1) == 0) && (c != '\n')){
				c = fgetc(s1);
			}
			if (c != '\n'){
				return;
			}
		}
	}
	scanf ("%c", &q);
	while ((q != 'q') && (feof(s1) == 0)){
		for (int i = 0; i < mode2; i++){
			c = fgetc(s1);
			count = 0;
			while ((feof(s1) == 0) && (c != '\n')){
				count++;
				printf("%c", c);
				c = fgetc(s1);
			}
			if (c == '\n'){
				if (mode1){
					if (count == 0){
						if (ok == 0){
							ok = 1;
							printf("\n");
						}
					}
					else{
						ok = 0;
						printf("\n");
					}
				}
				else {
					printf("\n");
				}
			}
			else {
				return;
			}
		}
		scanf ("%c", &q);
		scanf ("%c", &q);
	}
	return;
}
int from_str_to_unsint(char *str){
	int x = 0, i = 0;
	char c;
	c = str[i];
	while ((c >= '0') && (c <= '9')){
		x = (x * 10) + c - '0';
		i++;
		c = str[i];
	}
	if (c == '\0'){
		return x;
	}
	else{
		return -1;
	}
}