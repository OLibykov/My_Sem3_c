#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list{
	char *string;
	struct list *next;
} list;

typedef struct tree{
	char *string;
	struct tree *left;
	struct tree *right;
} tree;

typedef struct word{
	char letter;
	struct word *next;
} word;

list *create(list *st);
void delete(list *st);
void out(list *st);
list *sort(list *st);
tree *create_tree(tree *tr, list *st);
tree *add_elem(tree *tr, char *string);
void out_tr(tree *tr);
void del_word(word *wor);
void free_tr(tree *tr);

int main (){
	list *st = NULL;
	tree *tr = NULL;
	st = create(st);
	out(st);
	tr = create_tree(tr, st);
	out_tr(tr);
	delete(st);
	free_tr(tr);
	tr = NULL;
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
void delete(list *st){
	list *hlp;
	while (st->next != NULL) {
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
tree *create_tree(tree *tr, list *st){
	while(st->next != NULL){
		tr = add_elem(tr, st->string);
		st = st->next;
	}
	return tr;
}
tree *add_elem(tree *tr, char *st){
	if (tr == NULL) {
		tr = (tree*)malloc(sizeof(tree));
		tr->string = st;
		tr->left = NULL;
		tr->right = NULL;
	}
	else if (strcmp(tr->string, st) > 0){;
		tr->left = add_elem(tr->left, st);
	}
	else if (strcmp(tr->string, st) < 0){
		tr->right = add_elem(tr->right, st);
	}
	return tr;
}
void out_tr(tree *tr) {
	if (tr != NULL){
		out_tr(tr->left);
		printf("%s ", tr->string);
		out_tr(tr->right);
	}
	return;
}
void free_tr(tree *tr) {
	if (tr != NULL){
		free_tr(tr->left);
		free_tr(tr->right);
		free(tr->string);
		free(tr);
	}
	return;
}