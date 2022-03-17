#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

struct MainCommand  {
    char* InputFile;
    char* OutputFile;
    bool IfAppend;
    bool background;
    char*** pipe;
};

struct Input {
    int N;
    char* error;
    bool is_eof;
    struct MainCommand* commands;
};

// структуры для выполнения команд

struct DynamicArrayOfArrays{
    char*** arrof;
    int N;
    int cap;
};

struct DynamicArray {
    char** arr;
    int N;
    int cap;
};

struct DynamicString {
    char* str;
    int N;
    int cap;
};

// "Рабочие" структуры


void InitInput(struct Input* input) {
    input->N = 0;
    input->commands = (struct MainCommand*)malloc((input->N+1)
                                                  * sizeof(struct MainCommand));
    input->error = NULL;
    input->is_eof = false;
}

bool IsStrEquals(char* s1, char* s2) {
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        ++s1;
        ++s2;
    }
    return (*s1 == *s2);
}

void FreeString(struct DynamicString* string) {
    string->N = 0;
    string->cap = 0;
    free(string->str);
    string->str = NULL;
}

struct DynamicString InitString() {
    struct DynamicString string;
    string.N=0;
    string.cap=1;
    string.str=(char*) malloc(string.cap * sizeof(char));
    (string.str)[0]='\0';
    
    return string;
} // инициализация строки

void FreeArray(struct DynamicArray* array) {
    array->N = 0;
    array->cap = 0;
    char** word_ptr = array->arr;
    while (*word_ptr != NULL) {
      free(*word_ptr);
      ++word_ptr;
    }
    free(array->arr);
}

struct DynamicArray InitArray() {
    struct DynamicArray array;
    array.N = 0;
    array.cap = 1;
    array.arr = (char**)malloc(array.cap * sizeof(char*));
    (array.arr)[0] = NULL;

    return array;
} // инициализация массива


struct DynamicArrayOfArrays InitArrayofArrays() {
    struct DynamicArrayOfArrays arrayof;
    arrayof.N = 0;
    arrayof.cap = 1;
    arrayof.arrof = (char***)malloc(arrayof.cap * sizeof(char**));
    (arrayof.arrof)[0] = NULL;
    return arrayof;
} // инициализвация массива массивов

void AddChar(struct DynamicString* string, char f) {
    char* new;
    int i=0;
    if (string->N + 1 < string->cap) {
        string->str[string->N] = f ;
        string->str[string->N+1] = '\0' ;
    }
    else
    {
        new = string->str;
        string->cap +=1;
        string->str = (char*)malloc(string->cap * sizeof(char)) ;
        while (new[i] != '\0'){
            string->str[i] = new[i] ;
            i++;
        }
        string->str[i] = f;
        string->str[i+1] = '\0' ;
        free(new);
    }
    i = 0;
    string->N += 1;
} // добавление одного элемента в строку

void AddString(struct DynamicArray* array, char* f) {
    if (array->N+1 >= array->cap) {
        char** new = array->arr;
        array->cap +=1;
        array->arr = (char**)malloc(array->cap * sizeof(char*)) ;
        for (int i = 0; i < array->N ; i++) {
            array->arr[i] = new[i];
        }
        free(new);
    }
    array->arr[array->N] = f;
    array->arr[array->N+1] = NULL;
    array->N += 1;
} // добавление строки в массив

void AddArray (struct DynamicArrayOfArrays* arrayof, char** f) {
    if (arrayof->N+1 >= arrayof->cap) {
        char*** new;
        new = arrayof->arrof;
        arrayof->cap +=1;
        arrayof->arrof = (char***)malloc(arrayof->cap * sizeof(char**)) ;
        for (int i = 0; i < arrayof->N ; i++) {
            arrayof->arrof[i] = new[i];
        }
        free(new);
    }
    arrayof->arrof[arrayof->N] = f;
    arrayof->arrof[arrayof->N+1] = NULL;
    arrayof->N += 1;
}

char ToChange(int f, char** File) {
    struct DynamicString string = InitString();
    while (f == ' ') {
        f = getchar();
    }
    while (f != '\n' && f != EOF && f != ' ') {
        AddChar(&string, f);
        f = getchar();
    }
    (*File) = string.str;
    return f;
}

void AddCommand(struct Input* input, char*** array,
                char* Input, char* Output, bool type) {
    struct MainCommand command;
    command.InputFile = Input;
    command.OutputFile = Output;
    command.IfAppend = type;
    command.background = false;
    command.pipe = array;
    if (input->N == 0) {
        input->commands[0] = command;
    }
    else {
        struct MainCommand* new;
        new = input->commands;
        input->commands = (struct MainCommand*)malloc((input->N+1)
                                                      * sizeof(struct MainCommand));
        for(int i = 0; i< input->N ; i++) {
            input->commands[i] = new[i];
            input->commands[i].background = true;
        }
        input->commands[input->N] = command;
        free(new);
    }
    input->N += 1;
} // добавление команды в структуру

void PrintArray(char** array) {
    int i = 0;
    printf("     ");
    while (array[i] != NULL) {
        printf("%s ", array[i]);
        i++;
    }
    printf("\n");
}

void PrintArrayofArrays (struct DynamicArrayOfArrays* arrayof) {
    for (int i = 0; i < arrayof->N ; i++) {
        printf("%d:", i);
        PrintArray(arrayof->arrof[i]);
    }
}

void ReadInput(struct DynamicString* string,
               struct DynamicArray* array,
               struct DynamicArrayOfArrays* arrayof,
               struct Input* input) {
    int f = getchar();
    while (f == ' ') {
        f = getchar();
    }
    char* Input = NULL;
    char* Output = NULL;
    bool type = false;
    while (f != '\n' && f != EOF) {
        if (f == ' ') {
            while (f == ' ') {
                f = getchar();
            }
            if (string->str[0] != '\0') {
                AddString(array, string->str);
                (*string) = InitString();
            }
        }
        else if (f == '&') {
            
            if (string->str[0] != '\0') {
                AddString(array, string->str);
            }
            if (array->arr[0] != NULL) {
                AddArray(arrayof, array->arr);
            }
            if (arrayof->arrof[0] != NULL){
                AddCommand(input, arrayof->arrof, Input, Output, type);
                Input = NULL;
                Output = NULL;
            }
            (*string) = InitString();
            (*array) = InitArray();
            (*arrayof) = InitArrayofArrays();
            f = getchar();
            while (f == ' ') {
                f = getchar();
            }
        }
        else if (f == '|') {
            if (string->str[0] != '\0') {
                AddString(array, string->str);
            }
            AddArray(arrayof, array->arr);
            (*array) = InitArray();
            (*string) = InitString();
            f = getchar();
            while (f == ' ') {
                f = getchar();
            }
        }
        else if (f == '>') {
            f = getchar();
            if (f == '>') {
				f = getchar();
                f = ToChange(f, &Output);
                type = true;
            }
            else {
                f = ToChange(f, &Output);
            }
            while (f == ' ') {
                f = getchar();
            }
        }
        else if (f == '<') {
            f = getchar();
            f = ToChange(f, &Input);
            while (f == ' ') {
                f = getchar();
            }
        }
        else {
            AddChar(string, f);
            f = getchar();
        }
    }
    if(string->str[0] != '\0') {
        AddString(array, string->str);
    }
    if (array->arr[0] != NULL) {
        AddArray(arrayof, array->arr);
    }
    if (arrayof->arrof[0] != NULL ){
        AddCommand(input, arrayof->arrof, Input, Output, type);
    }
    else if (arrayof->arrof[0] == NULL){
        input->commands[input->N-1].background = true;
    }
    if (f == EOF) {
        input-> is_eof = true;
    }
} // чтение потока символов, заполнение струткры для выполнения


void PrintCommands (struct Input* input) {
    for (int i = 0 ; i < input->N ; i++) {
        printf("Command %d\n", i);
        printf("   InputFile : %s\n", input->commands[i].InputFile);
        printf("   OutputFile : %s\n", input->commands[i].OutputFile);
        printf("   IfAppend : %d\n", input->commands[i].IfAppend);
        printf("   backgroud : %d\n", input->commands[i].background);
        printf("   pipe : \n");
        int j = 0;
        while (input->commands[i].pipe[j] != NULL) {
            PrintArray(input->commands[i].pipe[j]);
            j+=1;
        }
    }
}
// функции для отладки

void PrintDirectory() {
    char PathName[256];
    char* PN;
    PN = getwd (PathName);
    printf ("%s$ ",PathName);
}


void close_pipes(int* pipes, int pipes_size) {
  for (int i = 0; i < pipes_size; i++) {
    close(pipes[i]);
  }
}

bool RunInputEmbedded(struct Input* input) { // починить для >1 команды
    if (IsStrEquals(input->commands[0].pipe[0][0], "exit")) {
        if (input->commands[0].pipe[0][1] == NULL) {
            input->is_eof = true;
        }
        else {
            input->error = "exit does not expect arguments";
        }
        return true;
    }
    if (IsStrEquals(input->commands[0].pipe[0][0], "cd")) {
        if (input->commands[0].pipe[0][1] == NULL ||
            input->commands[0].pipe[0][2] != NULL ) {
    // Если нет аргументов ИЛИ аргументов более одного
            input->error = "cd expects exactly one argument";
        }
        else if (chdir(input->commands[0].pipe[0][1]) == -1) {
            input->error = "failed to change current working dir";
        }
        return true;
    }
    return false;
}

void RunPipe(struct Input* input, int number) {
    int j = 0;
    while (input->commands[number].pipe[j] != NULL) {
        j += 1;
    }
    int n = j;
    int pipes_size = (n - 1) * 2;
    int* pipes = (int*)malloc(pipes_size * sizeof(int));
    for (int i = 0; i < pipes_size; i += 2) {
        if (pipe(pipes + i) == -1) {
            input->error = "Error: Failed to make a pipe!\n";
            return ;
        }
    }
    int* childs = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        if (input->error != NULL) {
            return;
        }
        if ((IsStrEquals(input->commands[number].pipe[i][0], "exit"))
            || (IsStrEquals(input->commands[number].pipe[i][0], "cd"))) {
            input->error = "cd or exit is not expected in pipe";
            return;
        }
        int child = fork();
        if (child == -1) {
            input->error = "Error: Failed to fork!\n";
            return;
        }

        if (child == 0) { //сын
			if (n == 1 && 0 && input->commands[number].background){// фоновый режим
				int fd;
				signal (SIGINT, SIG_IGN);
				fd = open("/dev/null", O_RDWR, 0666);
				dup2(fd, 0);
				dup2(fd, 1);
			}
            int saved_stdout = dup(1);
            if (saved_stdout == -1) {
                input->error = "Error: Failed to dup STDOUT\n";
                return;
            }
            
            if (!(input->commands[number].InputFile == NULL)) {
                int file_desc = open(input->commands[number].InputFile , O_RDWR, 0777);
                dup2(file_desc, 0);
                close(file_desc);
            }
            
            if (!(input->commands[number].OutputFile == NULL)) {
                if (input->commands[number].IfAppend == 1) {
                    int file_desc = open(input->commands[number].OutputFile
                                         ,O_RDWR | O_APPEND, 0777);
                    dup2(file_desc, 1);
                    close(file_desc);
                }
                else {
                   int file_desc = open(input->commands[number].OutputFile
                                        ,O_RDWR | O_CREAT | O_TRUNC, 0777);
                    dup2(file_desc, 1);
                    close(file_desc);
                }
            }
            
            if (i > 0) {
                if (dup2(pipes[(i - 1) * 2], 0) == -1) {
                    input->error = "Error: Failed to dup2!\n";
                    return;
                }
            }
            
            if (i + 1 < n) {
                if (dup2(pipes[i * 2 + 1], 1) == -1) {
                    input->error = "Error: Failed to dup2!\n";
                    return;
                }
            }
            close_pipes(pipes, pipes_size);
            free(pipes);
            execvp(input->commands[number].pipe[i][0], input->commands[number].pipe[i]);
            dup2(saved_stdout, 1);
			close(saved_stdout);
            close_pipes(pipes, pipes_size);
            free(childs);
            input->error = "Error: Failed to execvp!";
            return;
        }
        else { // отец
            if (n == 1) {
                if (input->commands[number].background && i == 0){
                    printf("[%d] %d\n", i+1, child);
                }
                else {
                    waitpid(child, NULL, 0);
                }
            }
            else {
                childs[i] = child;
            }
        }
    }
    close_pipes(pipes, pipes_size);
    free(pipes);
    if (n != 1 && !(input->commands[number].background)) {
        for (int i = 0; i < n; i++) {
            if (waitpid(childs[i], NULL, 0) == -1) {
                printf("Error: Failed to wait child process #%d with pid %d\n", i,
                       childs[i]);
            }
        }
    }
    free(childs);
}

void RunInput(struct Input* input) {
    for (int i = 0; i < input->N; i++) {
        if (input->error != NULL) {
            return;
        }

        if (input->commands[i].pipe[0][0] == NULL) {
            return;
        }

        if (RunInputEmbedded(input)) {
            return;
        }
        RunPipe(input, i);
    }
}

void PrintError(struct Input* input) {
    if (input->error == NULL) {
        return;
    }
    printf("%s\n", input->error);
}

void FreeInput(struct Input* input) {
    for (int i = 0 ; i < input->N ; i++) {
        int j = 0;
        while(input->commands[i].pipe[j] != NULL) {
            char** tofree = input->commands[i].pipe[j];
            while (*tofree != NULL) {
                free(*tofree);
                ++tofree;
            }
            free(*tofree);
            free(input->commands[i].pipe[j]);
            j++;
        }
        free(input->commands[i].pipe[j]);
        free(input->commands[i].InputFile);
        free(input->commands[i].OutputFile);
    }
    free(input->commands);
}

int main () {
    struct Input input;
    do {
        PrintDirectory();
    // вывод директории
        struct DynamicString string = InitString();
        struct DynamicArray array = InitArray();
        struct DynamicArrayOfArrays arrayof = InitArrayofArrays();
        InitInput(&input);
    // объявление структур
        ReadInput(&string,&array,&arrayof,&input);
    // ввод и распределние по массива
        // PrintCommands(&input);
        RunInput(&input);
        PrintError(&input);
        FreeInput(&input);
        int wait_result = 0;
        while ((wait_result = waitpid(-1, NULL, WNOHANG)) > 0) {
            printf ("DONE\n");
        }
    }
    while (!input.is_eof);
}
