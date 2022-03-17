#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main (){
	int pid;
	int semid;
	int shmid;
	int *shmaddr;
	
	if ((semid = semget(IPC_PRIVATE, 1, IPC_CREAT|0666)) == -1){
		printf("Не получилось создать Семафор");
		return 0;
	}
	if ((shmid = shmget(IPC_PRIVATE, 10 * sizeof(int), IPC_CREAT|0666)) == -1){
		printf("Не получилось создать разделяемую память");
		return 0;
	}

	
struct sembuf lock[1] = {{0, -1, 0}};
struct sembuf unlock[1] = {{0, 1, 0}};
	
	semctl(semid, 0, SETVAL, (int) 1);
	shmaddr = shmat(shmid, NULL, 0);
	
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			*(shmaddr + 3 * i + j) = -1;
		}
		*(shmaddr + 9) = 0;
	}
	
	if ((pid = fork()) < 0){
		printf("Ошибка создания процесса");
	}
	
	else if (pid == 0){//сын
		shmaddr = shmat(shmid, NULL, 0);
		int x, y;
		while (1){
			semop(semid, lock, 1);
			if (*(shmaddr + 9) < 9){
				printf ("Введите ваш ход\n");
				scanf ("%d%d/n", &x, &y);
				while (*(shmaddr + x * 3 + y) != -1){		
					printf ("Поле занято");
					scanf ("%d%d/n", &x, &y);
				}
				*(shmaddr + x * 3 + y) = 1;
				(*(shmaddr + 9))++;
				for (int i = 0; i < 3; i++){
					for (int j = 0; j < 3; j++){
						printf("%d", *(shmaddr + 3 * i + j));
					}
					printf("\n");
				}
				semop(semid, unlock, 1);
			}
			else {
				semop(semid, unlock, 1);
				shmdt(shmaddr);
				return 0;
			}
		}
	}
	else {//отец
		int x, y;
		while (1){
			if (*(shmaddr + 9) < 9){
				semop(semid, lock, 1);
				if (*(shmaddr + 9) < 9){
					printf ("Введите ваш ход\n");
					scanf ("%d%d/n", &x, &y);
					while (*(shmaddr + x * 3 + y) != -1){		
						printf ("Поле занято");
						scanf ("%d%d/n", &x, &y);
					}
					*(shmaddr + x * 3 + y) = 0;
					(*(shmaddr + 9))++;
					for (int i = 0; i < 3; i++){
						for (int j = 0; j < 3; j++){
							printf("%d", *(shmaddr + 3 * i + j));
						}
						printf("\n");
					}
				}
				semop(semid, unlock, 1);
			}
			else {
				semop(semid, unlock, 1);
				shmdt(shmaddr);
				break;
			}
		}
	}
	waitpid(pid, NULL, 0);
	shmctl (shmid, IPC_RMID, NULL);
	semctl (semid, 0, IPC_RMID, (int) 0);
	return 0;
}