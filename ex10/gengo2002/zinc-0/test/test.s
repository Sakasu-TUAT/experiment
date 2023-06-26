.globl _main

.text
	.align 2
	.type	_main, @function
_main:
	pushl %ebp               # 00000000 55
	movl %esp,%ebp           # 00000001 89 e5
	subl $4, %esp            # 00000003 83 ec 04
	movl $0, %eax            # 00000006 c7 c0 00000000
	movl %eax, -4(%ebp)      # 0000000c 89 45 fc
L.1:
	movl $9, %eax            # 0000000f c7 c0 00000009
	pushl %eax               # 00000015 50
	movl -4(%ebp), %eax      # 00000016 8b 45 fc
	popl %ecx                # 00000019 59
	cmpl %ecx, %eax          # 0000001a 39 c8
	movl $0, %eax            # 0000001c c7 c0 00000000
	jnle L.3                 # 00000022 7f 02
	notl %eax                # 00000024 f7 d0
L.3:
	andl %eax, %eax          # 00000026 21 c0
	jz L.2                   # 00000028 74 2c
	movl -4(%ebp), %eax      # 0000002a 8b 45 fc
	pushl %eax               # 0000002d 50
	movl $48, %eax           # 0000002e c7 c0 00000030
	popl %ecx                # 00000034 59
	addl %ecx, %eax          # 00000035 01 c8
	int $193                 # 00000037 cd c1
	movl $32, %eax           # 00000039 c7 c0 00000020
	int $193                 # 0000003f cd c1
	movl $1, %eax            # 00000041 c7 c0 00000001
	pushl %eax               # 00000047 50
	movl -4(%ebp), %eax      # 00000048 8b 45 fc
	popl %ecx                # 0000004b 59
	addl %ecx, %eax          # 0000004c 01 c8
	movl %eax, -4(%ebp)      # 0000004e 89 45 fc
	jmp L.1                  # 00000051 e9 ffffffb9
L.2:
	movl $10, %eax           # 00000056 c7 c0 0000000a
	int $193                 # 0000005c cd c1
	leave                    # 0000005e c9
	ret                      # 0000005f c3
