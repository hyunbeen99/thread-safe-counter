#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
	int val;
	struct semid_ds *buf;
	ushort *array;
};

#define PATH "/home/hyunbeen"

typedef struct __counter_t {
    int value;
    pthread_mutex_t lock;
	union semum arg;
} counter_t;

unsigned int loop_cnt;
counter_t counter;

void init(counter_t *c);

//lock
void increment(counter_t *c) {
	struct sembuf s;
	s.sem_num = 0;
	s.sem_op = -1;
	s.sem_flg = 0;
	semop(semid, &s, 1);

	decrement(&counter);
}

//unlock
void decrement(counter_t *c) {
	struct sembuf s;
	s.sem_num = 0;
	s.sem_op = 1;
	s.sem_flg = 0;
	semop(semid, &s, 1);
}

int get(counter_t *c) {
	
    return rc;
}

void *mythread(void *arg)
{
    char *letter = arg;
    int i;

    printf("%s: begin\n", letter);
    for (i = 0; i < loop_cnt; i++) {
        increment(&counter);
    }
    printf("%s: done\n", letter);
    return NULL;
}
                                                                             
int main(int argc, char *argv[])
{                    
    loop_cnt = atoi(argv[1]);

    init(&counter);

    pthread_t p1, p2;
    printf("main: begin [counter = %d]\n", get(&counter));
    pthread_create(&p1, NULL, mythread, "A"); 
    pthread_create(&p2, NULL, mythread, "B");
    // join waits for the threads to finish
    pthread_join(p1, NULL); 
    pthread_join(p2, NULL); 
    printf("main: done [counter: %d] [should be: %d]\n", get(&counter), loop_cnt * 2);
    return 0;
}

void init(counter_t *c) {
	c->key = ftok(PATH, 'z');

	if (c->key < 0){
		perror(argv[0]);
		exit(1);
	}
	semid = semget(key, 1, 0600 | IPC_CREAT);
	if (semid < 0){
		perror(argv[0]);
		exit(1);
	printf("semid = %d\n", semid);
}
