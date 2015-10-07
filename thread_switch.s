# thread_switch fucntion
# %rdi the first arguments
# %rsi the second arguments

.globl thread_switch
thread_switch:
	pushq %rbx		#callee-save

	pushq %rbp
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15

	movq %rsp, (%rdi)

	movq (%rsi), %rsp

	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %rbp

	popq %rbx		#callee-restore
	ret
	