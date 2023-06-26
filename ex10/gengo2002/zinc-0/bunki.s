.globl _main

.lcomm x, 4
.lcomm z, 4

.text
	.align 2
	.type	_main, @function
_main:
	pushl %ebp
	movl %esp, %ebp
	movl $96, %eax
	movl %eax, x
	movl x, %eax
	movl %eax, z
	movl $0, %eax
	pushl %eax
	movl $2, %eax
	pushl %eax
	movl x, %eax
	popl %ecx
	cltd
	idivl %ecx, %eax
	movl %edx, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	jne L.2
	notl %eax
L.2:
	andl %eax, %eax
	jz L.1
	movl $0, %eax
	pushl %eax
	movl $3, %eax
	pushl %eax
	movl x, %eax
	popl %ecx
	cltd
	idivl %ecx, %eax
	movl %edx, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	jne L.4
	notl %eax
L.4:
	andl %eax, %eax
	jz L.3
	movl $6, %eax
	pushl %eax
	movl x, %eax
	popl %ecx
	cltd
	idivl %ecx, %eax
	movl %eax, z
L.3:
L.1:
	call putword
	movl $10, %eax
	int $193
	leave
	ret

.text
	.align 2
	.type	putword, @function
putword:
	pushl %ebp
	movl %esp, %ebp
	subl $4, %esp
	movl z, %eax
	movl %eax, -4(%ebp)
	movl $0, %eax
	pushl %eax
	movl z, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	jnl L.6
	notl %eax
L.6:
	andl %eax, %eax
	jz L.5
	movl $45, %eax
	int $193
	movl z, %eax
	negl %eax
	movl %eax, z
L.5:
	call putword0
	movl -4(%ebp), %eax
	movl %eax, z
	leave
	ret

.text
	.align 2
	.type	putword0, @function
putword0:
	pushl %ebp
	movl %esp, %ebp
	subl $4, %esp
	movl $10, %eax
	pushl %eax
	movl z, %eax
	popl %ecx
	cltd
	idivl %ecx, %eax
	movl %edx, %eax
	movl %eax, -4(%ebp)
	movl z, %eax
	pushl %eax
	movl $10, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	jnle L.8
	notl %eax
L.8:
	andl %eax, %eax
	jz L.7
	movl $10, %eax
	pushl %eax
	movl z, %eax
	popl %ecx
	cltd
	idivl %ecx, %eax
	movl %eax, z
	call putword0
L.7:
	movl -4(%ebp), %eax
	pushl %eax
	movl $48, %eax
	popl %ecx
	addl %ecx, %eax
	int $193
	leave
	ret
