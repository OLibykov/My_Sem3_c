#include <stdio.h>

const int z = 0x80000000;
void bin(unsigned int n);
int shift(unsigned int n, int k, char dir);


int main () {
	int n, k;
	char dir;
	while (scanf("%u", &n)){// для выхода введите не число
		scanf ("%d", &k);
		fflush(stdin);
		dir = getchar();//после fflush остается символ переноса строки
		dir = getchar();
		bin(n);
		bin(shift(n, k, dir));
	}
	return 0;
}

void bin(unsigned n) {
	unsigned int a = z;
	for (int i = sizeof(int) * 8 - 1; i >= 0 ; i--) {
	printf("%d", ((n & a) >> i));
		a >>= 1;
	}
	printf("\n");
	return;
}
int shift(unsigned int n, int k, char dir) {
	if (dir == 'r') { 
		for (int i = 0; i < k; i++) {
			if (n % 2 == 1) {
				n >>= 1;
				n += z;
			}
			else {
				n >>= 1;
			}	
		}					
	}
	else {
		for (int i = 0; i < k; i++) {
			if ((n & z) != 0) {
				n <<= 1;
				n += 1;
			}
			else {
				n <<= 1;
			}	
		}			
	}
	return n;
}