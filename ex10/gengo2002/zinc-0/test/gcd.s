.globl _main

.lcomm x, 4
.lcomm y, 4
.lcomm z, 4

.text
	.align 2
	.type	_main, @function
_main:
	pushl %ebp
	movl %esp, %ebp
	movl $7, %eax
	pushl %eax
	movl $1203, %eax
	popl %ecx
	imull %ecx, %eax
	movl %eax, x
	movl $7, %eax
	pushl %eax
	movl $371, %eax
	popl %ecx
	imull %ecx, %eax
	movl %eax, y
	call gcd
	call putword
	movl $10, %eax
	int $193
	leave
	ret

.text
	.align 2
	.type	gcd, @function
gcd:
	pushl %ebp
	movl %esp, %ebp
	subl $12, %esp
	movl y, %eax
	pushl %eax
	movl x, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	jng L.2
	notl %eax
L.2:
	andl %eax, %eax
	jz L.1
	movl x, %eax
	movl %eax, -4(%ebp)
	movl y, %eax
	movl %eax, -8(%ebp)
L.1:
	movl y, %eax
	pushl %eax
	movl x, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	jnle L.4
	notl %eax
L.4:
	andl %eax, %eax
	jz L.3
	movl y, %eax
	movl %eax, -4(%ebp)
	movl x, %eax
	movl %eax, -8(%ebp)
L.3:
L.5:
	movl $0, %eax
	pushl %eax
	movl -8(%ebp), %eax
	pushl %eax
	movl -4(%ebp), %eax
	popl %ecx
	cltd
	idivl %ecx, %eax
	movl %edx, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	je L.7
	notl %eax
L.7:
	andl %eax, %eax
	jz L.6
	movl -8(%ebp), %eax
	movl %eax, -12(%ebp)
	movl -8(%ebp), %eax
	pushl %eax
	movl -4(%ebp), %eax
	popl %ecx
	cltd
	idivl %ecx, %eax
	movl %edx, %eax
	movl %eax, -8(%ebp)
	movl -12(%ebp), %eax
	movl %eax, -4(%ebp)
	jmp L.5
L.6:
	movl -8(%ebp), %eax
	movl %eax, z
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
	jnl L.9
	notl %eax
L.9:
	andl %eax, %eax
	jz L.8
	movl $45, %eax
	int $193
	movl z, %eax
	negl %eax
	movl %eax, z
L.8:
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
	jnle L.11
	notl %eax
L.11:
	andl %eax, %eax
	jz L.10
	movl $10, %eax
	pushl %eax
	movl -4(%ebp), %eax
	pushl %eax
	movl z, %eax
	popl %ecx
	subl %ecx, %eax
	popl %ecx
	cltd
	idivl %ecx, %eax
	movl %eax, z
	call putword0
L.10:
	movl -4(%ebp), %eax
	pushl %eax
	movl $48, %eax
	popl %ecx
	addl %ecx, %eax
	int $193
	leave
	ret
