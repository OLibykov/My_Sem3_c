#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ad 8;

char *re();

int main () {
	char *p = NULL;
	p = re();
	printf("\n");
	puts(p);
	printf("%s", p);
	free(p);
	p = NULL;
	return 0;
}

char *re() {
	char *p;
	int count = 0, siz = ad;
	char c;
	p = malloc (siz * sizeof(char));
	c = getchar();
	while ((c != EOF) && (c != '\n')) {
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
