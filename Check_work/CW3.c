#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

const int SIZ = 10;
typedef struct List{
	char *string;
	struct List *next;
} list;

list *create(list *st);
void delete(list *st);
void out(list *st);
void changes(list *st);
bool find(char *str, char c);
list *chandel(list *st);
bool finend(char *str, char c);

int main (){
	list *st;
	st = create(st);
	out(st);
	changes(st);
	out(st);
	st = chandel(st);
	out(st);
	delete(st);
	st = NULL;
}
list *create(list *st){
	list *hlp;
	char c;
	int count;
	hlp = (list*)malloc(sizeof (list));
	st = hlp;
	hlp->string = NULL;
	hlp->next = NULL;
	c = getchar(); 
	while ((c != '\n') && (c != EOF)){
		hlp->string = (char*)malloc(SIZ * sizeof(char));
		hlp->string[0] = c;
		c = getchar();
		count = 1;
		while ((c != '\n') && (c != EOF) && (c != ' ')){
			hlp->string[count] = c;
			count++;
			c = getchar();
		}
		hlp->string[count] = '\0';
		hlp->next = (list*)malloc(sizeof(list));
		hlp = hlp->next;
		hlp->string = NULL;
		hlp->next = NULL;
		if (c == ' ') c = getchar();
	}
	return st;
}
void delete(list *st){
	list *hlp;
	while (st->next != NULL) {
		free(st->string);
		hlp = st->next;
		free(st);
		st = hlp;
	}
	free(st);
	return;
}
void out(list *st) {
	while (st->next != NULL){
		printf("%s ", st->string);
		st = st->next;
	}
	printf("\n");
	return;
}
void changes(list *st){
	list *hlp;
	char *new = {"111"};
	char c;
	c = getchar();
	while (st->next != NULL){
		hlp = st->next;
		if (find(st->string, c)){
			st->next = (list*)malloc(sizeof(list));
			st = st->next;
			st->string = (char*)malloc(SIZ * sizeof(char));
			st->string = strcpy(st->string, new);
			st->next = hlp;
		}
		st = st->next;
	}
	return;
}
bool find(char *str, char c){
	int count = 0;
	bool ok = 0;
	while (str[count] != '\0') {
		if (str[count] == c) {
			ok = 1;
			break;
		}
		count++;
	}
	return ok;
}

list *chandel(list *st){
	list *hlp1;
	list *hlp2 = st;
	char c;
	c = getchar();
	c = getchar();
	while (hlp2->next != NULL){
		hlp1 = hlp2->next;
		if (finend(hlp2->string, c)){
			free(hlp2->string);
			free(hlp2);
			st = hlp1;
		}
		else break;
		hlp2 = hlp1;
	}
	while (hlp1->next != NULL){
		if (finend(hlp1->string, c)){
			free(hlp1->string);
			hlp1 = hlp1->next;
			free(hlp2->next);
			hlp2->next = hlp1;
		}
		else {
			hlp2 = hlp1;
			hlp1 = hlp1->next;
		}
	}
	return st;
}
bool finend(char *str, char c){
	int count = 0;
	while (str[count] != '\0') count++;
	if (count != 0) {
		if (str[count - 1] == c) return 1;
	}
	return 0;
}


