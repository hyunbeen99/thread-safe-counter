#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
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
	key_t key;
    int value;
    int semid;
	union semun arg;
} counter_t;

unsigned int loop_cnt;
counter_t counter;

int init(counter_t *c);
void lock(counter_t *c);
void unlock(counter_t *c);

void increment(counter_t *c) {
	lock(&c);
	c->value++;
	unlock(&c);
}
void decrement(counter_t *c) {
	lock(&c);
	c->value--;
	unlock(&c);
}

int get(counter_t *c) {
	lock(&c);
	int rc = c->value;
	unlock(&c);
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

    int k;
	int s;

	k, s = init(&counter);

	if (k < 0){
		perror(argv[0]);
		exit(1);
	}
	if (s < 0){
		perror(argv[0]);
		exit(1);
	}
	printf("semid=%d\n", s);

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

int init(counter_t *c) {
	c->key = ftok(PATH, 'z');
	c->value = 0;
	c->semid = semget(c->key, 1, 0600 | IPC_CREAT);
	c->arg.val = 1;
	semctl(c->semid, 0, SETVAL, c->arg);

	return c->key, c->semid;
}

void lock(counter_t *c){
	struct sembuf s;
	s.sem_num = 0;
	s.sem_op = -1;
	s.sem_flg = 0;
	semop(c->semid, &s, 1);
}

void unlock(counter_t *c){
	struct sembuf s;
	s.sem_num = 0;
	s.sem_op = 1;
	s.sem_flg = 0;
	semop(c->semid, &s, 1);
}
