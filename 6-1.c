#include <stdio.h>

#define BINPRINT(x){ \
for (int i = 8 * sizeof(x) - 1; i >= 0; i--)\
{\
	if ((x) & (1 << i)){ \
		printf("%c", '1');\
	}\
	else {\
		printf("%c", '0');\
	}\
} \
}

int main(){
	char c = -2;
	if (c){
		BINPRINT(c);
	}
	else {
		printf("ZERO\n");
	}
	printf("\n");
	BINPRINT((short)7);
	printf("\n");
	int a = -500;
	if (a){
		BINPRINT(a);
	}
	else {
		printf("ZERO\n");
	}
	printf("\n");
	long long int x = 15;
	if (x) {
		BINPRINT (x);
	}
	else {
		printf("ZERO\n");
	}
	printf("\n");
    BINPRINT((long) x);
	return 0;
}
