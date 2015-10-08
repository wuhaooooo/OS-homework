#include "assignment.c"

struct thread* current_thread;
struct thread* inactive_thread;

int main(){
	
	current_thread = malloc(sizeof(struct thread));
	inactive_thread = malloc(sizeof(struct thread));


	current_thread->initial_function = fun_with_threads;
	int* p = malloc(sizeof(int));
	*p = 5;
	current_thread->initial_argument = p;
	current_thread->stack_pointer = malloc(STACK_SIZE) + STACK_SIZE;
	//current_thread->initial_function(current_thread->initial_argument);

	thread_start(inactive_thread, current_thread);


	return 0;
}
