/*

Tiny ZiNC Compiler --- code generater


Copyright (C) 2000  KISHIMOTO, Makoto

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


	KISHIMOTO, Makoto <cs96068@cs.tuat.ac.jp>

*/

/*

	コードジェネレータ

*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "confdef.h"

#include "express.h"
#include "name.h"
#include "labelgen.h"

#include "codegen.h"

static void gen_add_grp(exp_node *p, char const op[]);
static void gen_cmp_grp(exp_node *p, char const op[]);

static FILE *out_file;

void
init_codegen(FILE *fp)
{
  out_file = fp;
}

void
gen_verb(char s[])
{
  fprintf(out_file, "%s", s);
}

void
gen_make_frame(int size)
{
  fprintf(out_file, "\tsubl $%d, %%esp\n", size);
}

void
gen_exp(exp_node *p)
{
  switch (p->type)
    {
    case EXP_ISEQ:
      gen_cmp_grp(p, "jne");  /* 条件の反転に注意 */
      break;
    case EXP_ISNOTEQ:
      gen_cmp_grp(p, "je");  /* 条件の反転に注意 */
      break;
    case EXP_ISLT:
      gen_cmp_grp(p, "jnl");  /* 条件の反転に注意 */
      break;
    case EXP_ISGT:
      gen_cmp_grp(p, "jng");  /* 条件の反転に注意 */
      break;
    case EXP_ISLTEQ:
      gen_cmp_grp(p, "jnle");  /* 条件の反転に注意 */
      break;
    case EXP_ISGTEQ:
      gen_cmp_grp(p, "jnge");  /* 条件の反転に注意 */
      break;

    case EXP_ADD:
      gen_add_grp(p, "addl");
      break;
    case EXP_SUB:
      gen_add_grp(p, "subl");
      break;
    case EXP_OR:
      gen_add_grp(p, "orl");
      break;

    case EXP_MUL:
      gen_exp(p->val._2._1);
      fprintf(out_file, "\tpushl %%eax\n");
      gen_exp(p->val._2._0);
      fprintf(out_file, "\tpopl %%ecx\n");
      fprintf(out_file, "\timull %%ecx, %%eax\n");
      break;
    case EXP_DIV:
      gen_exp(p->val._2._1);
      fprintf(out_file, "\tpushl %%eax\n");
      gen_exp(p->val._2._0);
      fprintf(out_file, "\tpopl %%ecx\n");
      fprintf(out_file, "\tcltd\n");
      fprintf(out_file, "\tidivl %%ecx, %%eax\n");
      break;
    case EXP_MOD:
      gen_exp(p->val._2._1);
      fprintf(out_file, "\tpushl %%eax\n");
      gen_exp(p->val._2._0);
      fprintf(out_file, "\tpopl %%ecx\n");
      fprintf(out_file, "\tcltd\n");
      fprintf(out_file, "\tidivl %%ecx, %%eax\n");
      fprintf(out_file, "\tmovl %%edx, %%eax\n");
      break;
    case EXP_LSL:
      gen_exp(p->val._2._1);
      fprintf(out_file, "\tpushl %%eax\n");
      gen_exp(p->val._2._0);
      fprintf(out_file, "\tpopl %%ecx\n");
      fprintf(out_file, "\tshll %%cl, %%eax\n");
      break;
    case EXP_ASR:
      gen_exp(p->val._2._1);
      fprintf(out_file, "\tpushl %%eax\n");
      gen_exp(p->val._2._0);
      fprintf(out_file, "\tpopl %%ecx\n");
      fprintf(out_file, "\tsarl %%cl, %%eax\n");
      break;
    case EXP_LSR:
      gen_exp(p->val._2._1);
      fprintf(out_file, "\tpushl %%eax\n");
      gen_exp(p->val._2._0);
      fprintf(out_file, "\tpopl %%ecx\n");
      fprintf(out_file, "\tshrl %%cl, %%eax\n");
      break;

    case EXP_AND:
      gen_add_grp(p, "andl");
      break;
    case EXP_NOT:
      gen_exp(p->val._1._0);
      fprintf(out_file, "\tnotl %%eax\n");
      break;
    case EXP_PLUS:
      gen_exp(p->val._1._0);
      break;
    case EXP_MINUS:
      gen_exp(p->val._1._0);
      fprintf(out_file, "\tnegl %%eax\n");
      break;

    case EXP_CONST:
      fprintf(out_file, "\tmovl $%d, %%eax\n", p->val.constval);
      break;
    case EXP_VAR:
      {
        name_type var_scope;
        var_scope = name_get_type(p->val.var);
        if (var_scope == NAME_GLO_VAR)
          {
            fprintf(out_file, "\tmovl %s, %%eax\n", name_get_str(p->val.var));
          }
        else if (var_scope == NAME_LOC_VAR)
          {
            fprintf(out_file, "\tmovl -%d(%%ebp), %%eax\n", name_get_id(p->val.var));
          }
        else
          {
            EMSTOP("internal conflict", 0);
            exit(1);
          }
        break;
      }
    }
}

static void
gen_add_grp(exp_node *p, char const op[])
{
  gen_exp(p->val._2._1);
  fprintf(out_file, "\tpushl %%eax\n");
  gen_exp(p->val._2._0);
  fprintf(out_file, "\tpopl %%ecx\n");
  fprintf(out_file, "\t%s %%ecx, %%eax\n", op);
}

static void
gen_cmp_grp(exp_node *p, char const op[])
{
  int label;

  gen_add_grp(p, "cmpl");
  fprintf(out_file, "\tmovl $0, %%eax\n");  /* 注 : ←ここを xorl %eax, %eax に */
  label = getnewnum();                      /*      しては **いけない** */
  fprintf(out_file, "\t%s L.%d\n", op, label);  /* なぜなら←ここで見ている */
  fprintf(out_file, "\tnotl %%eax\n");  /* フラグを破壊してしまうからである */
  gen_label(label);
}

void
gen_label(int n)
{
  fprintf(out_file, "L.%d:\n", n);
}

void
gen_goto(int n)
{
  fprintf(out_file, "\tjmp L.%d\n", n);
}

void
gen_jz(int n)
{
  fprintf(out_file, "\tjz L.%d\n", n);
}

void
gen_set(name_info *store_to)
{
  name_type var_scope;

  var_scope = name_get_type(store_to);
  if (var_scope == NAME_GLO_VAR)
    {
      fprintf(out_file, "\tmovl %%eax, %s\n", name_get_str(store_to));
    }
  else if (var_scope == NAME_LOC_VAR)
    {
      fprintf(out_file, "\tmovl %%eax, -%d(%%ebp)\n", name_get_id(store_to));
    }
  else
    {
      EMSTOP("internal conflict", 0);
      exit(1);
    }
}
