#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ad 4;

char *fin(char *substr, char *str, int cou_substr, int cou_str);
char *re(int *cou);

int main () {
	int cou_str;
	int cou_substr; 
	char *str = NULL;
	char *substr = NULL;
	char *found = NULL;
	str = re(&cou_str);
	substr = re(&cou_substr);
	if (cou_str < cou_substr) {
		printf("Not found");
	}
	else {
		found = fin(substr, str, cou_substr, cou_str);
		if (found == NULL) {
			printf("Not found");
		}
		else {
			printf("Found\n");
			printf("%s", found);
		}
	}

	free(str);
	free(substr);
	str = NULL;
	substr = NULL;
	return 0;
}

char *re(int *cou) {//через cou возвращаем длину строки
	char *p;
	int count = 0, siz = ad;
	char c;
	p = malloc (siz * sizeof(char));
	c = getchar();
	while ((c != EOF) && (c!='\n')) {
		p[count] = c;
		count++;
		if (count == siz) {
			siz += ad;
			p = realloc(p, siz * sizeof(char)); 
		}
		c = getchar(); 
	}
	p[count] = '\0';
	*cou = count;
	return p;
}

char *fin(char *substr, char *str, int cou_substr, int cou_str){
	char *hlp = NULL;
	bool ok;
	for (int i = 0; i <= (cou_str) - (cou_substr); i++) {
		if (str[i] == substr[0]) {
			bool ok = 1;
			for (int j = 0; j < cou_substr; j++) {
				if (str[i + j] != substr[j]) {
					ok = 0;
					break;
				}
			}
			if (ok){
				hlp = str + i;
			}
		}
	}
	return hlp;
}
