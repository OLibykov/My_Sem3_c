#include <stdio.h>
#include <sys/types.h>

int main(int argc, char **argv){
	char str[80];
	FILE *file;
	if (argc == 1){
		printf ("Input File");
	}
	else {
		printf ("%s", argv[1]);
	}
	file = fopen (argv[1], 'r');
	if (file == NULL){
		printf ("erroe opening file");

	while (!feof(file)){
		fgets(tr, 80, file);
		printf("%s", str);
	}
	return 0;
}
