#include <stdio.h>

void completion(int a[258][258], int n, int m);
int main() {
	int n, m;
	scanf ("%d%d", &n, &m);
	int a[258][258];
	completion(a, n, m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			printf("%4d ", a[i][j]);
		}
		printf("\n");
	}
	return 0;
}
void completion(int a[258][258], int n, int m){
	int x = 1, y = 1, turn = 0, dir = 0, count = 2;

	for (int i = 0; i <= n + 1; i++) {
		for (int j = 0; j <= m + 1; j++) {
			 a[i][j] = 0;
		}
	}
	a[y][x] = 1;
	while (turn < 4) {
		if (dir == 0) {//вниз
			if ((y + 1 > n) || (a[y + 1][x] != 0)) {
				dir++;
				turn++;
			}
			else {
				turn = 0;
				y++;
				a[y][x] = count;
				count++;
			}
		}
		else if (dir == 1) {//вправо
			if ((x + 1 > m) || (a[y][x + 1] != 0)) {
				dir++;
				turn++;
			}
			else {
				turn = 0;
				x++;
				a[y][x] = count;
				count++;
			}
		}
		else if (dir == 2) {//вверх
			if ((y - 1 < 1) || (a[y - 1][x] != 0)) {
				dir++;
				turn++;
			}
			else {
				turn = 0;
				y--;
				a[y][x] = count;
				count++;
			}
		}
		else if (dir == 3) {//влево
			if ((x - 1 < 1) || (a[y][x - 1] != 0)) {
				dir = 0;
				turn++;
			}
			else {
				turn = 0;
				x--;
				a[y][x] = count;
				count++;
			}
		}
	}
	return;
}
