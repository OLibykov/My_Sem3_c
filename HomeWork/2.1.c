#include <stdio.h>

double abc(double a); 

int main () {
	double e, x, tmp1, tmp2;
	scanf("%lf", &e);
	while (scanf("%lf", &x) == 1) {
		tmp1 = 1;
		tmp2 = (1 + x) / 2;
		while (abc (tmp2 - tmp1) >= e) {
			tmp1 = tmp2;
			tmp2 = (tmp2 + x / tmp2) / 2;
		} // в tmp2 ответ
		printf("%f\n", tmp2);
		printf("%.12F\n", tmp2);
		printf("%9F\n", tmp2);
		printf("%g\n", tmp2);
		printf("%20e\n", tmp2);
		printf("%.2E\n", tmp2);
		printf("%.11g\n", tmp2);
		printf("%.10g\n", tmp2);
		printf("%.G\n", tmp2);
	}
	
	return 0;
}
double abc(double a) {
	return (a > 0) ? a : -a;
}