#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>

void file_work1 (int d, int d1, int m);
void file_work2 (int d, int d2, int k, int len);
int from_str_to_unsint(char *str);
int num_line(int d);

int main (int argc, char **argv){
	int k, n, m, d, d1, d2, len;
	char c, c1 = '\n';
	struct stat st;
	
	if (argc != 4){
		printf("Неверное количество параметров\n");
		return 0;
	}
	n = from_str_to_unsint(argv[2]);
	if (n == -1){
		printf("Неверный формат числа\n");
		return 0;
	}
	m = from_str_to_unsint(argv[3]);
	if (m == -1){
		printf("Неверный формат числа\n");
		return 0;
	}
	d = open(argv[1], O_RDWR | O_APPEND, 0777);
	if (d == -1){ 
		printf ("Введите данные\n");
		d = open(argv[1], O_RDWR | O_CREAT | O_APPEND | O_EXCL, 0777);
		for (int i = 0; i < n; i++){
			c = getchar();
			while ((c != '\n') && (c != EOF)){
				write(d, &c, sizeof(char));
				c = getchar();
			}
			write(d, &c1, sizeof(char));
		}
	}
	printf("\nНомер индексного дискриптора = %d\n", d);
	len = lseek (d, 0, SEEK_END);
	lseek (d, 0, SEEK_SET);
	printf("\nДлина файла = %d\n", len);
	fstat(d, &st);
	printf("\nКоличество жестких ссылок = %d\n", st.st_nlink);
	len = num_line(d);
	d1 = open("fil.txt",  O_RDWR | O_CREAT | O_TRUNC, 0777);
	file_work1(d, d1, m);
	printf("k = ");
	scanf("%d", &k);
	d2 = open("fi.txt",  O_RDWR | O_CREAT | O_TRUNC, 0777);
	file_work2(d, d2, k, len);
	close(d);
	close(d2);
	return 0;
}

void file_work1(int d, int d1, int m){
	lseek(d, 0, SEEK_SET);
	lseek(d1, 0, SEEK_SET);
	unsigned char buf[1000] = {0};
	int z, i, count = 0;
	while (z = (read(d, buf, 1000))){
		i = 0;
		while (i < z){
			if (buf[i] == '\n'){
				count++;
				if ((count % m) == m - 1){
					i++;
					while ((buf[i] != '\n') && (i < z)){
						write (d1, &buf[i], 1);
						i++;
					}
					if (i == z){
						lseek(d, 1, SEEK_CUR);
						z = read(d, &(buf), 1000);
						i = 0;
						while ((buf[i] != '\n') && (i < z)){
							write (d1, &(buf[i]), 1);
							i++;
						}
					}
					write(d1, &(buf[i]), 1);
					count++;
				}
			}
			i++;
		}
		lseek(d, 1, SEEK_CUR);
		if (count - 1 < m){
			printf("В файле нет %d строк", m);
		}
	}
	lseek(d, 0, SEEK_SET);
	return;
}
int from_str_to_unsint(char *str){
	int x = 0, i = 0;
	char c;
	c = str[i];
	while ((c >= '0') && (c <= '9')){
		x = (x * 10) + c - '0';
		i++;
		c = str[i];
	}
	if (c == '\0'){
		return x;
	}
	else{
		return -1;
	}
}
int num_line(int d){
	lseek(d, 0, SEEK_SET);
	unsigned char buf[1000] = {0};
	unsigned count = 0, len;
	while((len  = read(d, buf, 1000)) > 0) {
		for(int i = 0; i < len; i++){
			if (buf[i] == '\n'){
				count++;
			}
		}
	}
	lseek(d, 0, SEEK_SET);
	return count;
}
void file_work2 (int d, int d2, int k, int len){
	if (len <= 2 * k){
		return;
	}
	bool ok = 1;
	char buf[1000] = {0};
	int count = 0, bys = 0, bye = 0, i, j = 0, z = 0;
	lseek(d, 0, SEEK_SET);
	lseek(d2, 0, SEEK_SET);
	
	while (ok){
		z  = read(d, buf, 1000);
		for (i = 0; i < z; i++){
			if (buf[i] == '\n'){
				count++;
				if (count == k){
					j = i;
				}
				else if (count == (len - k)){
					ok = 0;
					break;
				}
			}
		}
		if (j == 0){
			bys += i;
		}
		bye += i;
	}
	bys += j;
	lseek(d, bys + 1, SEEK_SET);
	while ((bye - bys) > 1000){
		read(d, buf, 1000);
		write(d2, buf, 1000);
		bye -= 1000;
	}
	read(d, buf, bye - bys);
	write(d2, buf, bye - bys);
	lseek(d, 0, SEEK_SET);
	lseek(d2, 0, SEEK_SET);
	return;
}