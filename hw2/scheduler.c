#include "scheduler.h"

struct thread * current_thread;
struct queue ready_list;

void yield(){
	struct thread* temp = current_thread;
	current_thread = inactive_thread;
	inactive_thread = temp;
	thread_switch(inactive_thread, current_thread);
};

void thread_wrap(){
	current_thread->initial_function(current_thread->initial_argument);
	while(1){
		yield();
	}
};

void scheduler_begin(){
	current_thread = malloc(sizeof(struct thread));
	current_thread->state = "RUNNING";
	ready_list.head = NULL;
	ready_list.tail = NULL;
};

void thread_fork(void(*target)(void*), void* arg) {

};