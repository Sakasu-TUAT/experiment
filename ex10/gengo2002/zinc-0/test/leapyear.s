.globl _main

.lcomm g_num, 4
.lcomm g_year, 4
.lcomm g_isleap, 4

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
	movl $0, %eax
	movl %eax, -4(%ebp)
L.1:
	movl $2000, %eax
	pushl %eax
	movl -4(%ebp), %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	jnle L.3
	notl %eax
L.3:
	andl %eax, %eax
	jz L.2
	movl -4(%ebp), %eax
	movl %eax, g_year
	call leapyear
	movl g_isleap, %eax
	andl %eax, %eax
	jz L.4
	movl -4(%ebp), %eax
	movl %eax, g_num
	call printdec
	movl $0, %eax
	pushl %eax
	movl $40, %eax
	pushl %eax
	movl $4, %eax
	pushl %eax
	movl -4(%ebp), %eax
	popl %ecx
	addl %ecx, %eax
	popl %ecx
	cltd
	idivl %ecx, %eax
	movl %edx, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	je L.6
	notl %eax
L.6:
	andl %eax, %eax
	jz L.5
	call space
L.5:
L.4:
	movl $0, %eax
	pushl %eax
	movl $40, %eax
	pushl %eax
	movl $4, %eax
	pushl %eax
	movl -4(%ebp), %eax
	popl %ecx
	addl %ecx, %eax
	popl %ecx
	cltd
	idivl %ecx, %eax
	movl %edx, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	jne L.8
	notl %eax
L.8:
	andl %eax, %eax
	jz L.7
	call linefeed
L.7:
	movl $1, %eax
	pushl %eax
	movl -4(%ebp), %eax
	popl %ecx
	addl %ecx, %eax
	movl %eax, -4(%ebp)
	jmp L.1
L.2:
	call linefeed
	leave
	ret

.text
	.align 2
	.type	leapyear, @function
leapyear:
	pushl %ebp
	movl %esp, %ebp
	movl $0, %eax
	movl %eax, g_isleap
	movl $0, %eax
	pushl %eax
	movl $4, %eax
	pushl %eax
	movl g_year, %eax
	popl %ecx
	cltd
	idivl %ecx, %eax
	movl %edx, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	jne L.10
	notl %eax
L.10:
	andl %eax, %eax
	jz L.9
	movl $1, %eax
	negl %eax
	movl %eax, g_isleap
L.9:
	movl $0, %eax
	pushl %eax
	movl $100, %eax
	pushl %eax
	movl g_year, %eax
	popl %ecx
	cltd
	idivl %ecx, %eax
	movl %edx, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	jne L.12
	notl %eax
L.12:
	andl %eax, %eax
	jz L.11
	movl $0, %eax
	movl %eax, g_isleap
L.11:
	movl $0, %eax
	pushl %eax
	movl $400, %eax
	pushl %eax
	movl g_year, %eax
	popl %ecx
	cltd
	idivl %ecx, %eax
	movl %edx, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	jne L.14
	notl %eax
L.14:
	andl %eax, %eax
	jz L.13
	movl $1, %eax
	negl %eax
	movl %eax, g_isleap
L.13:
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
	jnl L.16
	notl %eax
L.16:
	andl %eax, %eax
	jz L.15
	movl g_num, %eax
	negl %eax
	movl %eax, g_num
	movl $45, %eax
	int $193
L.15:
	movl $10, %eax
	pushl %eax
	movl g_num, %eax
	popl %ecx
	cltd
	idivl %ecx, %eax
	movl %edx, %eax
	movl %eax, -4(%ebp)
	movl $9, %eax
	pushl %eax
	movl g_num, %eax
	popl %ecx
	cmpl %ecx, %eax
	movl $0, %eax
	jng L.18
	notl %eax
L.18:
	andl %eax, %eax
	jz L.17
	movl $10, %eax
	pushl %eax
	movl g_num, %eax
	popl %ecx
	cltd
	idivl %ecx, %eax
	movl %eax, g_num
	call printdec
L.17:
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
