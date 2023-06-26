/*
グローバル変数へのアクセスのためのヘッダ
*/

#if !defined _EXTERN_H_
#define _EXTERN_H_

#define __P386_GLOBAL__ extern
#include "global.c"
#undef __P386_GLOBAL__

#endif /* _EXTERN_H_ */
