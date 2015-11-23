#include "scheduler.h"

struct thread * current_thread;
struct queue ready_list;
/*
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
*/

// yield is very similar to thread_fork, with the main difference being that 
// it is pulling the next thread to run off of the ready list instead of creating it. yield should:
void yield(){
	// If the current thread is not DONE, set its state to READY and enqueue it on the ready list.
	if(current_thread->state != DONE && current_thread->state != BLOCKED){
		current_thread->state = READY;
		thread_enqueue(&ready_list, current_thread);
	}
	// Dequeue the next thread from the ready list and set its state to RUNNING.
	struct thread* next_thread = thread_dequeue(&ready_list);
	next_thread->state = RUNNING;
	// Save a pointer to the current thread in a temporary variable, then set the current thread to the next thread.
	struct thread* temp = current_thread;
	current_thread = next_thread;
	// Call thread_switch with the old current thread as old and the new current thread as new.
	thread_switch(temp, current_thread);
};

void thread_wrap(){
	current_thread->initial_function(current_thread->initial_argument);
	current_thread->state = DONE;
	yield();
};

void scheduler_begin(){
	current_thread = malloc(sizeof(struct thread));
	current_thread->state = RUNNING;
	ready_list.head = NULL;
	ready_list.tail = NULL;
};

void thread_fork(void(*target)(void*), void* arg) {
	// allocate a new thread control block and stack
	struct thread* new_thread = malloc(sizeof(struct thread));
	new_thread->stack_pointer = malloc(STACK_SIZE) + STACK_SIZE;
	// Set the new thread's initial argument and initial function.
	new_thread->initial_function = target;
	new_thread->initial_argument = arg;
	// 	Set the current thread's state to READY and enqueue it on the ready list.
	if(current_thread->state != BLOCKED)
		current_thread->state = READY;
	thread_enqueue(&ready_list, current_thread);
	// Set the new thread's state to RUNNING.
	new_thread->state = RUNNING;
	// Save a pointer to the current thread in a temporary variable, then set the current thread to the new thread.
	struct thread* temp = current_thread;
	current_thread = new_thread;
	// Call thread_start with the old current thread as old and the new current thread as new.
	thread_start(temp, current_thread);
};

/*Finally, recall from the first assignment that we need a way 
to prevent the main thread from terminating prematurely 
if there are other threads still running. 
Implement a solution to this problem in scheduler_end. 
(Hint: you may find the is_empty queue function useful).*/
void scheduler_end(){
	while(is_empty(&ready_list) == 0){
		yield();
	}
};


void mutex_init(struct mutex * m){
	m->held = 0;
	m->waiting_threads.head = NULL;
	m->waiting_threads.tail = NULL;
};

void mutex_lock(struct mutex * m){
	if(m->held == 1){
		current_thread->state = BLOCKED;
		thread_enqueue(&m->waiting_threads, current_thread);
		yield();
	}else
		m->held = 1;
};

void mutex_unlock(struct mutex * m){
	if(is_empty(&m->waiting_threads)){
		m->held = 0;
	}else{
		struct thread* temp = thread_dequeue(&m->waiting_threads);
		if(temp){
			temp->state = READY;
			thread_enqueue(&ready_list, temp);
		}
	}
};
/*


void condition_init(struct condition *){};
void condition_wait(struct condition *, struct mutex *){};
void condition_signal(struct condition *){};
void condition_broadcast(struct condition *){};

*/
