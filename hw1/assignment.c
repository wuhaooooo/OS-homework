#include "assignment.h"

extern struct thread* current_thread;
extern struct thread* inactive_thread;

int factorial(int n){
	return n == 0 ? 1 : n * factorial(n-1);
};

void fun_with_threads(void* arg){
	int n = *(int*) arg;
	printf("%d!= %d\n", n, factorial(n));
};

void thread_wrap(){
	current_thread->initial_function(current_thread->initial_argument);
	yield();
};

void yield(){
	struct thread* temp = current_thread;
	current_thread = inactive_thread;
	inactive_thread = temp;
	thread_switch(inactive_thread, current_thread);
};