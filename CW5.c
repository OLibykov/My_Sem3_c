#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct word{
    unsigned int pos;
    unsigned int length;
} word;

void sort(word *x, int count);
word *file_work (FILE *s1, word *x, int *i);
void file_work_sort(FILE *s1, FILE *s2, word *x, int count);

int main (int argc, char **argv){
    word *x;
    int count;
    FILE *s1, *s2;
    if (argc != 2){
        printf("Неверное количество параметров");
        return 0;
    }
    s1 = fopen(argv[1], "r");
    if (s1 == NULL){
        perror("Ошибка чтения файла");
    }
    s2 = fopen("file(1).txt", "w");
    x = file_work(s1, x, &count);
    printf("%d\n", count);
    for (int i = 0; i < count; i++){
        printf("% d %d %d\n\n", i + 1, x[i].pos, x[i].length);
    }
    sort(x, count);
    for (int i = 0; i < count; i++){
        printf("%d %d %d\n", i + 1, x[i].pos, x[i].length);
    }
    file_work_sort(s1, s2, x, count);
    fclose(s1);
    fclose(s2);
    free(x);
    //remove(argv[1]);
    //rename("file(1).txt", argv[1]);
    return 0;
}

word *file_work(FILE *s1, word *x, int *i){
    char c;
    int count;
    int j = 0;
    x = (word*)malloc(100 * sizeof(word));
    while (feof(s1) == 0){
        c = fgetc(s1);
        count = 0;
        x[j].pos = ftell(s1);
        while ((c != '\n') && (c != EOF)) {
            count++;
            c = fgetc(s1);
        }
        x[j].length = count;
        j++;
         x = realloc(x, (j + 1) * sizeof(word));
    }
    *i = j;
    return x;
}
void sort(word *x, int count){
    int min, swap;
    for (int i = 0; i < count - 1; i++){
        min = i;
        for (int j = i + 1; j < count; j++){
            if (x[j].length < x[min].length){
                min = j;
            }
        }
        swap = x[min].pos;
        x[min].pos = x[i].pos;
        x[i].pos = swap;
        swap = x[min].length;
        x[min].length = x[i].length;
        x[i].length = swap;
    }
    return;
}
void file_work_sort(FILE *s1, FILE *s2, word *x, int count){
    char c;
    for (int i = 0; i < count; i++){
        fseek(s1, x[i].pos - 1, SEEK_SET);
        for (int j = 0; j < x[i].length; j++){
            c = fgetc(s1);
            fputc(c, s2);
        }
    }
    return;
}
