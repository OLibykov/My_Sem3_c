#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct list{
	char *string;
	struct list *next;
} list;

typedef struct word{
	char letter;
	struct word *next;
} word;

list *create(list *st);
void delete(list *st);
void out(list *st);
void outr(list *st);
list *sort(list *st);
void del_word(word *wor);

int main (){
	list *st;
	st = create(st);
	out(st);
	outr(st);
	printf("\n");
	st = sort(st);
	out(st);
	delete(st);
	st = NULL;
}
list *create(list *st){
	word *beg_wor;
	word *wor;
	list *str;
	char c;
	int count, max = 0; 
	wor = (word*)malloc(sizeof(word));
	wor->next = NULL;
	beg_wor = wor;
	str = (list*)malloc(sizeof(list));
	str->string = NULL;
	str->next = NULL;
	st = str;
	c = getchar();
	while ((c != '\n') && (c != EOF)){
		if (c != ' ') {
			count = 0;
			while ((c != ' ') && (c != '\n') && (c != EOF)){
				count++;
				wor->letter = c;
				if (count > max) {
					wor->next = (word*)malloc(sizeof(word));
					wor->next->next = NULL;
					max = count;
				}
				wor = wor->next;
				
				c = getchar();
			}
			wor = beg_wor;
			str->string = (char*)malloc((count + 1) * sizeof(char));
			for (int i = 0; i < count; i++){
				str->string[i] = wor->letter;
				wor = wor->next;
			}
			
			wor = beg_wor;
			str->string[count] = '\0';
			str->next = (list*)malloc(sizeof(list));
			str = str->next;
			str->string = NULL;
			str->next = NULL;
		}
		if (c == ' ') c = getchar();
	}
	del_word(beg_wor);
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
void out(list *st) {
	while (st->next != NULL){
		printf("%s ", st->string);
		st = st->next;
	}
	printf("\n");
	return;
}
void outr(list *st){
	if (st->next != NULL){
		outr(st->next);
		printf("%s ", st->string);
	}
	return;
}
list *sort(list *st){
	list *res = st;
	list *hlp;
	list *hlpl;
	list *res_st;
	list *find;
	list *lfind;
	bool ok = 1;
	while (st->next != NULL){
		hlpl = st;
		hlp = st->next;
		find = st;
		while(hlp->next != NULL){
			if (strcmp(find->string, hlp->string) > 0){
				find = hlp;
				lfind = hlpl;
			}
			hlp = hlp->next;
			hlpl = hlpl->next;
		} 
		if (ok) {
			ok = 0;
			res = find;
			res_st = res;
			if (find != st){
				lfind->next = find->next;
				res->next = st;
			}
			else {
				st = st->next;
			}
		}
		else {
			if (res_st->next != find) {
				lfind->next = find->next;
				find->next = res_st->next;
				res_st->next = find;
			
			}
			else {
				st = st->next;
			}
			res_st = res_st->next;	
		}
	}
	return res;
}
