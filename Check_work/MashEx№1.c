#include <stdio.h>
#include <stdlib.h>

#define ad 8;

char *re();
char *clean(char *p);
char *movr(char *p, int beg, int end);

int main () {
	char *p = NULL;
	char *s = NULL;
	p = re();
	printf("\n");
	puts(p);
	s = clean(p);
	puts(s);
	free(p);
	s = NULL;
	p = NULL;
	return 0;
}

char *re() {
	char *p;
	char *s;
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
	return p;
}
char *clean(char *p){
	char *hl = p;
	int count1 = 0, count2;
	while (hl[count1] != '\0') {
		if (hl[count1] == ' ') {
			count2 = count1 + 1;
			while ((hl[count2] == ' ') && (hl[count2] != '\0')) {
				count2++;
			}
			hl = movr(hl, count1 ,count2 - count1 - 1); 
			count1++;
		}

		else if ((hl[count1] == '/') && (hl[count1 + 1] == '*')){
			count2 = count1 + 2;
			while (((hl[count2] != '*') || (hl[count2 + 1] != '/')) && (hl[count2 + 1] != '\0')){
				count2++;
			}
			if (hl[count2 + 1] != '\0') {
				hl = movr(hl, count1 - 1 ,count2 - count1 + 2); 
				count1 -= 2;
			}
			count1++;
		}
		else {
			count1++;
		}
	}
	return hl;
}
char *movr(char *p, int beg, int count){
	if (count != 0) {
		for (int i = beg; i >= 0; i--) {
			p[i + count] = p[i];
		}
	}
	return (p + count);
}
