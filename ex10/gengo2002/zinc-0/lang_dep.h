/*

	zinc の処理系に依存する仕様に関する設定

*/

#if !defined _LANG_DEP_H_
#define _LANG_DEP_H_

#include "confdef.h"

typedef zinc_int32 zinc_word;  /* word の型 */
typedef zinc_u_int32 zinc_u_word;  /* word の型の符号無しの型 */

#define ZINC_WORD_MAX 0x7fffffff  /* zinc_word のとりうる最大の値 */
#define ZINC_SIZEOF_WORD 4

#define ZINC_C_NAME_MAX_LEN 511  /* 名前の最大バイト数 */

#endif /* _LANG_DEP_H_ */
