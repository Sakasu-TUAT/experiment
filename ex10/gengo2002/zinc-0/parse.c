#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "confdef.h"
#include "lang_dep.h"

#include "token.h"
#include "lex.h"
#include "name.h"
#include "express.h"
#include "codegen.h"
#include "labelgen.h"

#include "parse.h"

static void read_next(void);

static void module(void);
static void decl_proc(void);
static void define_glo_var(void);
static void define_proc(void);
static void define_loc_var(void);

static void statement(void);
static void comp_statement(void);
static void if_statement(void);
static void while_statement(void);
static void set_statement(void);
static void call_statement(void);
static void putchar_statement(void);

static exp_node *kakko_exp(void);
static exp_node *int_exp(void);
static exp_node *add_exp(void);
static exp_node *mul_exp(void);
static exp_node *unary_exp(void);
static exp_node *int_prim(void);

static token next;

static name_list *glo_name_list = 0;
static name_list *loc_name_list = 0;

void
init_parse(void)
{
  init_lex(stdin);
  init_codegen(stdout);
}

void
parse(void)
{
  read_next();  /* まず先読み */
  module();  /* プログラム全体は 1 個のモジュール定義 */
}

static void
read_next(void)
{
  next = lex();
}

static void
module(void)
{
  gen_verb(".globl _main\n\n");
  for (;;)
    {
      switch (next.lex)
        {
        case LEXVAL_PROC:
          decl_proc();
          break;
        case LEXVAL_WORD:
          define_glo_var();
          break;
        default:
          goto end_decl_g;  /* for (;;) を抜ける */
        }
    }
end_decl_g:
  while (next.lex == LEXVAL_DEFPROC)
    define_proc();

  if (next.lex != LEXVAL_eof)
    {
      EMSTOP("unknown token", get_linenum());
      exit(1);
    }
}

static void
decl_proc(void)
{
  name_info *thisname;

  do
    {
      read_next();
      if (next.lex != LEXVAL_name)
        {
          EMSTOP("proc name must be name", get_linenum());
          exit(1);
        }
      if (name_find(glo_name_list, (char *)next.sem.p) != 0)
        {
          EMSTOP("same (proc) name used twice", get_linenum());
          exit(1);
        }
      glo_name_list = name_append(glo_name_list, (char *)next.sem.p);
      thisname = name_find(glo_name_list, (char *)next.sem.p);
      name_set_decl(thisname);
      name_set_proc(thisname);
      read_next();
    }
  while (next.lex == ',');
  if (next.lex != ';')
    {
      EMSTOP("compiler expected \';\'", get_linenum());
      exit(1);
    }
  read_next();
}

static void
define_glo_var(void)
{
  name_info *thisname;

  do
    {
      read_next();
      if (next.lex != LEXVAL_name)
        {
          EMSTOP("global variable name must be name", get_linenum());
          exit(1);
        }
      if (name_find(glo_name_list, (char *)next.sem.p) != 0)
        {
          EMSTOP("same (global variable) name used twice", get_linenum());
          exit(1);
        }
      glo_name_list = name_append(glo_name_list, (char *)next.sem.p);
      thisname = name_find(glo_name_list, (char *)next.sem.p);
      name_set_def(thisname);
      name_set_glo_var(thisname);
      gen_verb(".lcomm ");
      gen_verb((char *)next.sem.p);
      gen_verb(", 4\n");
      read_next();
    }
  while (next.lex == ',');
  if (next.lex != ';')
    {
      EMSTOP("compiler expected \';\'", get_linenum());
      exit(1);
    }
  read_next();
}

static void
define_proc(void)
{
  name_info *thisname;

  read_next();
  if (next.lex != LEXVAL_name)
    {
      EMSTOP("proc name must be name", get_linenum());
      exit(1);
    }
  if ((thisname = name_find(glo_name_list, (char *)next.sem.p)) == 0)
    {
      EMSTOP("proc name is not declared", get_linenum());
      exit(1);
    }
  if (name_get_type(thisname) != NAME_PROC)
    {
      EMSTOP("name is not declared for procedure", get_linenum());
      exit(1);
    }
  if (name_get_stat(thisname) == NAME_DEFINED)
    {
      EMSTOP("same name proc defined twice", get_linenum());
      exit(1);
    }
  if (name_get_stat(thisname) != NAME_DECLARED)
    {
      EMSTOP("name is not declared", get_linenum());
      exit(1);
    }
  name_set_def(thisname);
  gen_verb("\n.text\n\t.align 2\n\t.type\t");
  gen_verb((char *)next.sem.p);
  gen_verb(", @function\n");
  gen_verb((char *)next.sem.p);
  gen_verb(":\n\tpushl %ebp\n\tmovl %esp, %ebp\n");
  read_next();
  if (next.lex != ':')
    {
      EMSTOP("compiler expected \':\'", get_linenum());
      exit(1);
    }
  read_next();
  define_loc_var();
  comp_statement();
  gen_verb("\tleave\n\tret\n");
  name_list_free(loc_name_list);
  loc_name_list = 0;
}

static void
define_loc_var(void)
{
  int frame_size;
  name_info *thisname;

  frame_size = 0;
  while (next.lex == LEXVAL_WORD)
    {
      do
        {
          read_next();
          if (next.lex != LEXVAL_name)
            {
              EMSTOP("local variable name must be name", get_linenum());
              exit(1);
            }
          if (name_find(loc_name_list, (char *)next.sem.p) != 0)
            {
              EMSTOP("same name local variable defined twice", get_linenum());
              exit(1);
            }
          frame_size += ZINC_SIZEOF_WORD;
          loc_name_list = name_append(loc_name_list, (char *)next.sem.p);
          thisname = name_find(loc_name_list, (char *)next.sem.p);
          name_set_def(thisname);
          name_set_loc_var(thisname);
          name_set_id(thisname, frame_size);
          read_next();
        }
      while (next.lex == ',');
      if (next.lex != ';')
        {
          EMSTOP("compiler expected \';\'", get_linenum());
          exit(1);
        }
      read_next();
    }
  if (frame_size > 0)
    gen_make_frame(frame_size);
}

static void
comp_statement(void)
{
  if (next.lex != '{')  /* このコメントは } エディタの括弧対応のためのおまじない */
    {
      EMSTOP("compiler expected \'{\'", get_linenum());   /* } */
      exit(1);
    }
  read_next();
  do
    statement();   /* { */
  while (next.lex != '}');
  read_next();
}

static void
statement(void)
{
  switch (next.lex)
    {
    case LEXVAL_IF:
      if_statement();
      break;
    case LEXVAL_WHILE:
      while_statement();
      break;
    case LEXVAL_SET:
      set_statement();
      break;
    case LEXVAL_CALL:
      call_statement();
      break;
    case LEXVAL_PUTCHAR:
      putchar_statement();
      break;
    default:
      EMSTOP("compiler expected statement", get_linenum());
      exit(1);
    }
}

static void
if_statement(void)
{
  int fi_label;

  fi_label = getnewnum();
  read_next();
  gen_exp(kakko_exp());
  gen_verb("\tandl %eax, %eax\n");
  gen_jz(fi_label);
  comp_statement();
  gen_label(fi_label);
}

static void
while_statement(void)
{
  int loop_label, quit_label;

  loop_label = getnewnum();
  quit_label = getnewnum();
  read_next();
  gen_label(loop_label);
  gen_exp(kakko_exp());
  gen_verb("\tandl %eax, %eax\n");
  gen_jz(quit_label);
  comp_statement();
  gen_goto(loop_label);
  gen_label(quit_label);
}

static void
set_statement(void)
{
  name_info *store_to;

  read_next();
  if (next.lex != LEXVAL_name)
    {
      EMSTOP("left of \":=\" must be name", get_linenum());
      exit(1);
    }
  store_to = name_find(loc_name_list, next.sem.p);
  if (store_to == 0)
    store_to = name_find(glo_name_list, next.sem.p);
  if (store_to == 0)
    {
      EMSTOP("left of \":=\" is unknown name",  get_linenum());
      exit(1);
    }
  if (name_get_type(store_to) == NAME_PROC)
    {
      EMSTOP("cannot assignment for procedure", get_linenum());
      exit(1);
    }
  read_next();
  if (next.lex != LEXVAL_coloneq)
    {
      EMSTOP("compiler expected \":=\"", get_linenum());
      exit(1);
    }
  read_next();
  if (next.lex == LEXVAL_GETCHAR)
    {
#if defined ZINC_FreeBSD
      gen_verb("\tpushl $___sF\n\tcall _fgetc\n\taddl $4, %esp\n");
#else /* ZINC_FreeBSD */
      gen_verb("\tint $192\n");
#endif /* ZINC_FreeBSD */
      read_next();
    }
  else
    {
      gen_exp(int_exp());
    }
  gen_set(store_to);
  if (next.lex != ';')
    {
      EMSTOP("compiler expected \';\'", get_linenum());
      exit(1);
    }
  read_next();
}

static void
call_statement(void)
{
  read_next();
  if (next.lex != LEXVAL_name)
    {
      EMSTOP("to call is must be name", get_linenum());
      exit(1);
    }
  gen_verb("\tcall ");
  gen_verb(next.sem.p);
  gen_verb("\n");
  read_next();
  if (next.lex != ';')
    {
      EMSTOP("compiler expected \';\'", get_linenum());
      exit(1);
    }
  read_next();
}

static void
putchar_statement(void)
{
  read_next();
  gen_exp(int_exp());
#if defined ZINC_FreeBSD
  gen_verb("\tpushl $___sF+88\n\tpushl %eax\n\tcall _fputc\n\taddl $8, %esp\n");
#else /* ZINC_FreeBSD */
  gen_verb("\tint $193\n");
#endif /* ZINC_FreeBSD */
  if (next.lex != ';')
    {
      EMSTOP("compiler expected \';\'", get_linenum());
      exit(1);
    }
  read_next();
}

static exp_node *
kakko_exp(void)
{
  exp_node *p;

  if (next.lex != '(')  /* このコメントは ) エディタの括弧対応のためのおまじない */
    {
      EMSTOP("compiler expected \'(\'", get_linenum());   /* ) */
      exit(1);
    }
  read_next();
  p = int_exp();   /* ( */
  if (next.lex != ')')
    {
      EMSTOP("compiler expected \')\'", get_linenum());   /* ) */
      exit(1);
    }
  read_next();

  return p;
}

static exp_node *
int_exp()
{
  exp_node *thisexp;

  thisexp = add_exp();
  while ((next.lex == LEXVAL_eqeq)
      || (next.lex == LEXVAL_bangeq)
      || (next.lex == '<')
      || (next.lex == '>')
      || (next.lex == LEXVAL_lt_or_eq)
      || (next.lex == LEXVAL_gt_or_eq))
    {
      exp_node *newexp;
      newexp = malloc(sizeof(exp_node));
      newexp->val._2._0 = thisexp;
      thisexp = newexp;
      switch (next.lex)
        {
        case LEXVAL_eqeq:
          newexp->type = EXP_ISEQ;
          break;
        case LEXVAL_bangeq:
          newexp->type = EXP_ISNOTEQ;
          break;
        case '<':
          newexp->type = EXP_ISLT;
          break;
        case '>':
          newexp->type = EXP_ISGT;
          break;
        case LEXVAL_lt_or_eq:
          newexp->type = EXP_ISLTEQ;
          break;
        case LEXVAL_gt_or_eq:
          newexp->type = EXP_ISGTEQ;
          break;
        default:
          EMSTOP("internal conflict", get_linenum());
          exit(1);
        }
      read_next();
      newexp->val._2._1 = add_exp();
    }

  return thisexp;
}

static exp_node *
add_exp(void)
{
  exp_node *thisexp;

  thisexp = mul_exp();
  while ((next.lex == '+')
      || (next.lex == '-')
      || (next.lex == '|'))
    {
      exp_node *newexp;
      newexp = malloc(sizeof(exp_node));
      newexp->val._2._0 = thisexp;
      thisexp = newexp;
      switch (next.lex)
        {
        case '+':
          newexp->type = EXP_ADD;
          break;
        case '-':
          newexp->type = EXP_SUB;
          break;
        case '|':
          newexp->type = EXP_OR;
          break;
        default:
          EMSTOP("internal conflict", get_linenum());
          exit(1);
        }
      read_next();
      newexp->val._2._1 = mul_exp();
    }

  return thisexp;
}

static exp_node *
mul_exp()
{
  exp_node *thisexp;

  thisexp = unary_exp();
  while ((next.lex == '*')
      || (next.lex == '/')
      || (next.lex == '%')
      || (next.lex == LEXVAL_lsl)
      || (next.lex == LEXVAL_asr)
      || (next.lex == LEXVAL_lsr)
      || (next.lex == '&'))
    {
      exp_node *newexp;
      newexp = malloc(sizeof(exp_node));
      newexp->val._2._0 = thisexp;
      thisexp = newexp;
      switch (next.lex)
        {
        case '*':
          newexp->type = EXP_MUL;
          break;
        case '/':
          newexp->type = EXP_DIV;
          break;
        case '%':
          newexp->type = EXP_MOD;
          break;
        case LEXVAL_lsl:
          newexp->type = EXP_LSL;
          break;
        case LEXVAL_asr:
          newexp->type = EXP_ASR;
          break;
        case LEXVAL_lsr:
          newexp->type = EXP_LSR;
          break;
        case '&':
          newexp->type = EXP_AND;
          break;
        default:
          EMSTOP("internal conflict", get_linenum());
          exit(1);
        }
      read_next();
      newexp->val._2._1 = unary_exp();
    }

  return thisexp;
}

static exp_node *
unary_exp()
{
  exp_node *op, *e, *thisexp;

  thisexp = 0;
  op = 0;

  while ((next.lex == '~')
      || (next.lex == '+')
      || (next.lex == '-'))
    {
      exp_node *old_op;
      old_op = op;
      op = malloc(sizeof(exp_node));
      if (thisexp == 0)
        thisexp = op;
      switch (next.lex)
        {
        case '~':
          op->type = EXP_NOT;
          break;
        case '+':
          op->type = EXP_PLUS;
          break;
        case '-':
          op->type = EXP_MINUS;
          break;
        default:
          EMSTOP("internal conflict", get_linenum());
          exit(1);
        }
      if (old_op != 0)
        old_op->val._1._0 = op;
      read_next();
    }
  e = int_prim();
  if (thisexp == 0)
    thisexp = e;
  else
    op->val._1._0 = e;

  return thisexp;
}

static exp_node *
int_prim()
{
  exp_node *thisexp;
  name_info *v;

  switch (next.lex)
    {
    case '(':   /* このコメントは ) エディタの括弧対応のためのおまじない */
      read_next();
      thisexp = int_exp();   /* ( */
      if (next.lex != ')')
        {   /* ( */
          EMSTOP("compiler expected \')\'", get_linenum());
          exit(1);
        }
      read_next();
      break;
    case LEXVAL_name:
      thisexp = malloc(sizeof(exp_node));
      thisexp->type = EXP_VAR;
      v = name_find(loc_name_list, next.sem.p);
      if (v == 0)
        v = name_find(glo_name_list, next.sem.p);
      if (v == 0)
        {
          EMSTOP("unknown name", get_linenum());
          exit(1);
        }
      if (name_get_type(v) == NAME_PROC)
        {
          EMSTOP("name of procedure cannot be refereed", get_linenum());
          exit(1);
        }
      thisexp->val.var = v;
      read_next();
      break;
    case LEXVAL_literal:
      thisexp = malloc(sizeof(exp_node));
      thisexp->type = EXP_CONST;
      thisexp->val.constval = next.sem.w;
      read_next();
      break;
    default:
      EMSTOP("expression is not correct", get_linenum());
      exit(1);
    }

  return thisexp;
}
