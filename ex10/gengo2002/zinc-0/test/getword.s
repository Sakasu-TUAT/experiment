.globl _main

.lcomm g_num, 4
.lcomm g_inputchar, 4

.text
	.align 2
	.type	_main, @function
_main:
	pushl %ebp
	movl %esp, %ebp
	call test
	leave
	ret

.text
	.align 2
	.type	test, @function
test:
	pushl %ebp
	movl %esp, %ebp
	subl $4, %esp
	int $192
	movl %eax, g_inputchar
L.1:
	movl $1, %eax
	negl %eax
	pushl %eax
	movl g_inputchar, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	je L.3
	notl %eax
L.3:
	andl %eax, %eax
	jz L.2
	call inputdec
	call printdec
	call linefeed
L.4:
	movl g_inputchar, %eax
	pushl %eax
	movl $57, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	jnl L.6
	notl %eax
L.6:
	pushl %eax
	movl $48, %eax
	pushl %eax
	movl g_inputchar, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	jnl L.7
	notl %eax
L.7:
	popl %ecx
	orl %ecx, %eax
	pushl %eax
	movl $1, %eax
	negl %eax
	pushl %eax
	movl g_inputchar, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	je L.8
	notl %eax
L.8:
	popl %ecx
	andl %ecx, %eax
	andl %eax, %eax
	jz L.5
	int $192
	movl %eax, g_inputchar
	jmp L.4
L.5:
	jmp L.1
L.2:
	leave
	ret

.text
	.align 2
	.type	inputdec, @function
inputdec:
	pushl %ebp
	movl %esp, %ebp
	movl $0, %eax
	movl %eax, g_num
	call inputdec0
	leave
	ret

.text
	.align 2
	.type	inputdec0, @function
inputdec0:
	pushl %ebp
	movl %esp, %ebp
	movl $57, %eax
	pushl %eax
	movl g_inputchar, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	jnle L.10
	notl %eax
L.10:
	pushl %eax
	movl g_inputchar, %eax
	pushl %eax
	movl $48, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	jnle L.11
	notl %eax
L.11:
	popl %ecx
	andl %ecx, %eax
	andl %eax, %eax
	jz L.9
	movl $48, %eax
	pushl %eax
	movl g_inputchar, %eax
	popl %ecx
	subl %ecx, %eax
	pushl %eax
	movl $10, %eax
	pushl %eax
	movl g_num, %eax
	popl %ecx
	imull %ecx, %eax
	popl %ecx
	addl %ecx, %eax
	movl %eax, g_num
	int $192
	movl %eax, g_inputchar
	call inputdec0
L.9:
	leave
	ret

.text
	.align 2
	.type	printdec, @function
printdec:
	pushl %ebp
	movl %esp, %ebp
	subl $4, %esp
	movl $0, %eax
	pushl %eax
	movl g_num, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	jnl L.13
	notl %eax
L.13:
	andl %eax, %eax
	jz L.12
	movl g_num, %eax
	negl %eax
	movl %eax, g_num
	movl $45, %eax
	int $193
L.12:
	call printdec0
	leave
	ret

.text
	.align 2
	.type	printdec0, @function
printdec0:
	pushl %ebp
	movl %esp, %ebp
	subl $4, %esp
	movl g_num, %eax
	movl %eax, -4(%ebp)
	movl $9, %eax
	pushl %eax
	movl -4(%ebp), %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	jng L.15
	notl %eax
L.15:
	andl %eax, %eax
	jz L.14
	movl $10, %eax
	pushl %eax
	movl -4(%ebp), %eax
	popl %ecx
	cltd
	idivl %ecx, %eax
	movl %eax, g_num
	movl $10, %eax
	pushl %eax
	movl -4(%ebp), %eax
	popl %ecx
	cltd
	idivl %ecx, %eax
	movl %edx, %eax
	movl %eax, -4(%ebp)
	call printdec
L.14:
	movl $48, %eax
	pushl %eax
	movl -4(%ebp), %eax
	popl %ecx
	addl %ecx, %eax
	int $193
	leave
	ret

.text
	.align 2
	.type	linefeed, @function
linefeed:
	pushl %ebp
	movl %esp, %ebp
	movl $10, %eax
	int $193
	leave
	ret

.text
	.align 2
	.type	space, @function
space:
	pushl %ebp
	movl %esp, %ebp
	movl $32, %eax
	int $193
	leave
	ret
