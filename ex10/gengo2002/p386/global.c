/*
グローバル変数
*/

#include <sys/types.h>
#include <setjmp.h>

#include "config.h"
#include "emulater.h"

#if !defined __P386_GLOBAL__
#define __P386_GLOBAL__
#endif

/* レジスタ */

__P386_GLOBAL__ u_int32_t p386_EAX;
__P386_GLOBAL__ u_int32_t p386_EBX;
__P386_GLOBAL__ u_int32_t p386_ECX;
__P386_GLOBAL__ u_int32_t p386_EDX;

__P386_GLOBAL__ u_int32_t p386_EBP;
__P386_GLOBAL__ u_int32_t p386_ESP;

__P386_GLOBAL__ u_int32_t p386_EIP;

__P386_GLOBAL__ u_int32_t p386_EFLAGS;

/* メモリ */

__P386_GLOBAL__ u_int8_t p386_text[P386_TEXT_SIZE];
__P386_GLOBAL__ u_int8_t p386_data[P386_DATA_SIZE];
__P386_GLOBAL__ u_int8_t p386_stack[P386_STACK_SIZE];

/* エミュレータ */

__P386_GLOBAL__ p386_state_t p386_state;
__P386_GLOBAL__ jmp_buf p386_jmpbuf_int3;
