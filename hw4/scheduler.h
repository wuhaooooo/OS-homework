#include <stdlib.h>
#include <stdio.h>
#include <aio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "queue.h"

#define STACK_SIZE 1024*1024
extern struct thread * current_thread;

typedef enum {
    RUNNING, // The thread is currently running.
    READY,   // The thread is not running, but is runnable.
    BLOCKED, // The thread is not running, and not runnable.
    DONE     // The thread has finished. 
} state_t;

struct thread {
	unsigned char* stack_pointer;
	void (*initial_function)(void*);
	void* initial_argument;
	state_t state;	
};

struct mutex {
	int held;
	struct queue waiting_threads;
};
/*

struct condition {
	struct queue waiting_threads;
};
*/

void scheduler_begin();
void thread_fork(void(*target)(void*), void* arg);
void yield();
void scheduler_end();

void mutex_init(struct mutex *);
void mutex_lock(struct mutex *);
void mutex_unlock(struct mutex *);

/*

void condition_init(struct condition *);
void condition_wait(struct condition *, struct mutex *);
void condition_signal(struct condition *);
void condition_broadcast(struct condition *);

*/
