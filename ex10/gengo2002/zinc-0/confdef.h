/*

	zinc コンパイラを生成する環境に合わせて変更するべき設定

*/

#if !defined _CONFDEF_H_
#define _CONFDEF_H_

#include <sys/types.h>
#include <stdio.h>

#define EMSTOP(mes, num) \
fprintf(stderr, "EMSTOP %s:%d " mes "(input line : %d)\n", \
        __FILE__, __LINE__, num);

typedef int zinc_int32;
typedef unsigned int zinc_u_int32;

#endif /* _CONFDEF_H_ */
#include <stdio.h>
