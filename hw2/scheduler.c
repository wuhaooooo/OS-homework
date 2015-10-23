#include "scheduler.h"

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