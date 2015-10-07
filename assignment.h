#include <stdlib.h>
#include <stdio.h>
#define STACK_SIZE 1024*1024

struct thread{
	unsigned char* stack_pointer;
	void (*initial_function)(void*);
	void* initial_argument;
};

int factorial(int n);

void fun_with_threads(void* arg);

void thread_switch(struct thread* old, struct thread* new);

void thread_start(struct thread * old, struct thread * new);

void thread_wrap();