#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct tree{
	int x;
	struct tree *left;
	struct tree *right;
} tree;

tree *create_tree(tree *tr, int *z, int x, bool *ok);
tree *add_elem(tree *tr, int x);
void out_tr(tree *tr);
void free_tr(tree *tr);
tree *delete(tree *tr, int x);

int main (){
	int x;
	int y;
	int z;
	bool ok = 1;
	tree *tr = NULL;
	while (scanf ("%d", &x)){
		y = x;
		tr = create_tree(tr, &z, x, &ok);
		out_tr(tr);
		printf("\n");
		printf("%d\n", z);
		tr = delete(tr, z);
		out_tr(tr);
		printf("\n");
		printf("%d\n", y);
		tr = delete(tr, y);
		out_tr(tr);
		free_tr(tr);
		tr = NULL;
		if (ok != 1) break;
	}
	return 0;
}

tree *create_tree(tree *tr, int *z, int x, bool *ok){
	while ((x != 0) && (*ok == 1)){
		tr = add_elem(tr, x);
		*z = x;
		*ok = scanf("%d", &x);
	}
	return tr;
}
tree *add_elem(tree *tr, int x){
	if (tr == NULL) {
		tr = (tree*)malloc(sizeof(tree));
		tr->x = x;
		tr->left = NULL;
		tr->right = NULL;
	}
	else if (tr->x > x){;
		tr->left = add_elem(tr->left, x);
	}
	else if (tr->x < x){
		tr->right = add_elem(tr->right, x);
	}
	return tr;
}
void out_tr(tree *tr) {
	if (tr != NULL){
		out_tr(tr->right);
		printf("%d ", tr->x);
		out_tr(tr->left);
	}
	return;
}
void free_tr(tree *tr) {
	if (tr != NULL){
		free_tr(tr->left);
		free_tr(tr->right);
		free(tr);
	}
	return;
}
tree *delete(tree *tr, int x){
	tree *hlp;
	tree *hlp2;
	if (x == tr->x) {
		if ((tr->left == NULL) && (tr->right == NULL)){
			free(tr);
			tr = NULL;
		}
		else if (tr->left == NULL){
			hlp = tr->right;
			free(tr);
			tr = hlp;
		}
		else if (tr->right == NULL){
			hlp = tr->left;
			free(tr);
			tr = hlp;
		}
		else {
			hlp = tr->left;
			hlp2 = tr;
			while (hlp->right != NULL){
				hlp2 = hlp;
				hlp = hlp->right;
			}
			if (hlp2 != tr) {
				hlp2->right = hlp->left;
				hlp->right = tr->right;
				hlp->left = tr->left;
				free(tr);
				tr = hlp;
			}
			else {
				hlp->right = tr->right;
				free(tr);
				tr = hlp;
			}
		}
	}
	else if (x > tr->x) {
		if (tr->right != NULL){
			tr->right = delete(tr->right, x);
		}
	}
	else {
		if (tr->left != NULL){
			tr->left = delete(tr->left, x);
		}
	}
	return tr;
}
