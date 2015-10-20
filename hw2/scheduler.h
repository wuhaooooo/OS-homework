#include <stdlib.h>
#include <stdio.h>
#define STACK_SIZE 1024*1024

struct thread{
	unsigned char* stack_pointer;
	void (*initial_function)(void*);
	void* initial_argument;
};

void scheduler_begin();
void thread_fork(void(*target)(void*), void* arg);
void yield();
void scheduler_end();

extern struct* current_thread;
