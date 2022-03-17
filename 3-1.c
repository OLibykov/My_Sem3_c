#include <stdio.h>
#include <stdlib.h>

const int z = 0x80000000;
const int ad = 5;
void bin(int n);
void sor(int *p, int count); 
int count_bin(int n);
int main () {
	int count = 0, siz = ad;
	int *p = NULL;
	char c;
	p = malloc (siz * sizeof(int));
	while (scanf("%d", &(p[count])) == 1) {
		count++;
		c = getchar();
		if (c == '\n') break;
		if (count == siz) {
			siz += ad;
			p = realloc(p, siz * sizeof(int)); 
		}
	}
	for (int i = 0; i < count; i++) {
		printf("%d ", p[i]);
	}
	printf ("\n");
	for (int i = 0; i < count; i++) {
		bin(p[i]);
	}
	
	sor (p, count);
	
	for (int i = 0; i < count; i++) {
		printf("%d ", p[i]);
	}
	printf ("\n");
	free(p);
	p = NULL;
	return 0;
}
void bin(int n) {
	unsigned int a = z;
	for (int i = sizeof(int) * 8 - 1; i >= 0 ; i--) {
	printf("%d", ((n & a) >> i));
		a >>= 1;
	}
	printf("\n");
	return;
}
void sor(int *p, int count) {
	int f, hlp;
	for (int i = 0; i < count - 1; i++) {
		f = i;
		for (int j = i + 1; j < count; j++) {
			if ((count_bin(p[f]) > count_bin(p[j])) || ((count_bin(p[f]) == count_bin(p[j])) & (p[j] > p[f]))) f = j; 
		}
		hlp = p[f];
		p[f] = p[i];
		p[i] = hlp;
	}
}

int count_bin(int n){
	int count = 0;
	unsigned int a = z;
	for (int i = sizeof(int) * 8 - 1; i >= 0 ; i--) {
		count += (n & a) >> i;
		a >>= 1;
	}
	return count;
}

