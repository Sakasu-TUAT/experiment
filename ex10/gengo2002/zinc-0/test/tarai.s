.globl _main

.lcomm x, 4
.lcomm y, 4
.lcomm z, 4
.lcomm r, 4

.text
	.align 2
	.type	_main, @function
_main:
	pushl %ebp
	movl %esp, %ebp
	movl $12, %eax
	movl %eax, x
	movl $6, %eax
	movl %eax, y
	movl $0, %eax
	movl %eax, z
	call tarai
	leave
	ret

.text
	.align 2
	.type	tarai, @function
tarai:
	pushl %ebp
	movl %esp, %ebp
	subl $24, %esp
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
	movl %eax, -12(%ebp)
	movl z, %eax
	movl %eax, -20(%ebp)
	movl $1, %eax
	pushl %eax
	movl -4(%ebp), %eax
	popl %ecx
	subl %ecx, %eax
	movl %eax, x
	call tarai
	movl r, %eax
	movl %eax, -8(%ebp)
	movl $1, %eax
	pushl %eax
	movl -12(%ebp), %eax
	popl %ecx
	subl %ecx, %eax
	movl %eax, x
	movl -20(%ebp), %eax
	movl %eax, y
	movl -4(%ebp), %eax
	movl %eax, z
	call tarai
	movl r, %eax
	movl %eax, -16(%ebp)
	movl $1, %eax
	pushl %eax
	movl -20(%ebp), %eax
	popl %ecx
	subl %ecx, %eax
	movl %eax, x
	movl -4(%ebp), %eax
	movl %eax, y
	movl -12(%ebp), %eax
	movl %eax, z
	call tarai
	movl -8(%ebp), %eax
	movl %eax, x
	movl -16(%ebp), %eax
	movl %eax, y
	movl r, %eax
	movl %eax, z
	call tarai
	movl r, %eax
	movl %eax, y
L.1:
	movl y, %eax
	movl %eax, r
	leave
	ret
