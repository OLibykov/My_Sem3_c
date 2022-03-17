#include <stdio.h>
#include <stdbool.h>

int palin(int n1, int n2);

int main () {
	int n1 = 1, n2;
	while (n1 != 0) {
		scanf("%d",&n1);
		if (n1 == 0) break;
		scanf("%d", &n2);
		if (n1 > n2) {
			printf("incorrect data. Try again.\n");
			continue;
		}
		printf("count = %d\n", palin(n1, n2));
	}
	return 0;
}

int palin(int n1, int n2) {
	int k, hlp, count = 0;
	bool ok;
	for (int i = n1; i <= n2; i++) {
		ok = true;
		k = 1;
		hlp = i / 10;
		while (hlp > 0) {
			k *= 10;
			hlp /= 10;
		}
		hlp = i; 
		while (hlp > 9) {
			if ((hlp / k) != (hlp % 10)) {
				ok = false;
				break;
			}
			if ((hlp / (k / 10)) % 10 == 0) { // проверяем 2 слева цифру
				if ((hlp / 10) % 10 == 0) { // проверяем 2 справа цифру
					hlp += 10; // добавляем ко 2 ой цифре слева и справа по 1, иначе 0 сократятся
					hlp += k / 10;
				}
				else {
					ok = false;
					break;
				}
			}
			hlp = (hlp % k) / 10;
			k /= 100;
		}
		if (ok) {
			count++;
			printf("%d\n", i); 
		}
	}
	return count;
}