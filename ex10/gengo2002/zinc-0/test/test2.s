.globl _main


.text
	.align 2
	.type	_main, @function
_main:
	pushl %ebp
	movl %esp,%ebp
	subl $4, %esp
	movl $3, %eax
	pushl %eax
	movl $1, %eax
	popl %ecx
	shll %cl, %eax
	movl %eax, -4(%ebp)
	movl $3, %eax
	pushl %eax
	movl $5, %eax
	popl %ecx
	sarl %cl, %eax
	movl %eax, -4(%ebp)
	movl $3, %eax
	pushl %eax
	movl $5, %eax
	popl %ecx
	shrl %cl, +0(%ebp)
	movl %eax, -4(%ebp)
	leave
	ret
