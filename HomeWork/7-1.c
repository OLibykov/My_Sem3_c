#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/file.h>
#include <sys/types>
#include <unistd>

typedef struct word{
	char letter;
	struct word *next;
} word;

void file_work (FILE *s1, FILE *s2, int x);
void del_word(word *wor);
int from_str_to_unsint(char *str);

int main (int argc, char **argv){
	int x;
	FILE *s1, *s2;
	if (argc != 3){
		printf("Неверное количество параметров\n");
		return 0;
	}
	x = from_str_to_unsint(argv[2]);
	if (x == -1){
		printf("Неверный формат числа\n");
		return 0;
	}
	s1 = fopen(argv[1], "r");
	if (s1 == NULL){
		perror("Ошибка чтения файла\n");
		return 0;
	}
	s2 = fopen("file(1).txt", "w"); 
	if (x > 0){
		file_work(s1, s2, x);
	}
	fclose(s1);
	fclose(s2);
	remove(argv[1]);
	rename("file(1).txt", argv[1]);
	return 0;
}

void file_work(FILE *s1, FILE *s2, int x){
	word *beg_wor;
	word *wor;
	char c;
	int count, max = 0; 
	wor = (word*)malloc(sizeof(word));
	wor->next = NULL;
	beg_wor = wor;
	while (feof(s1) == 0){
		c = fgetc(s1);
		count = 0;
		while ((c != '\n') && (c != EOF)) {
			count++;
			wor->letter = c;
			if (count > max) {
				wor->next = (word*)malloc(sizeof(word));
				wor->next->next = NULL;
				max = count;
			}
			wor = wor->next;
			c = fgetc(s1);
		}
		if (count >= x){
			wor = beg_wor;
			for (int i = 0; i < count; i++){
				fputc(wor->letter, s2);
				wor = wor->next;
			}
			if (c == '\n'){
				fputc(c, s2);
			}
		}
		wor = beg_wor;
	}
	del_word(beg_wor);
	return;
}
void del_word(word *wor){
	word *hlp;
	while (wor->next != NULL){
		hlp = wor->next;
		free(wor);
		wor = hlp;
	}
	free(wor);
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