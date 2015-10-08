# initial a new thread
.globl thread_start

thread_start:

	pushq %rbx		#callee-save

	pushq %rbp
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15

	movq %rsp, (%rdi)

	movq (%rsi), %rsp

	jmp thread_wrap
	

