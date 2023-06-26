#if !defined _LEX_H_
#define _LEX_H_

#include "token.h"

void init_lex(FILE *fp);
token const lex(void);
int get_linenum(void);

#endif /* _LEX_H_ */
