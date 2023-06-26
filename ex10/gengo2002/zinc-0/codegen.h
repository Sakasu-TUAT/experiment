#if !defined _CODEGEN_H_
#define _CODEGEN_H_

#include <stdio.h>

#include "express.h"
#include "name.h"

void init_codegen(FILE *fp);
void gen_verb(char s[]);
void gen_make_frame(int size);
void gen_exp(exp_node *p);
void gen_label(int n);
void gen_goto(int n);
void gen_jz(int n);
void gen_set(name_info *store_to);

#endif /* _CODEGEN_H_ */
