#if !defined _EXPRESS_H_
#define _EXPRESS_H_

#include "lang_dep.h"
#include "name.h"

typedef struct exp_node_ exp_node;

typedef enum exp_type_ {
  EXP_ISEQ,
  EXP_ISNOTEQ,
  EXP_ISLT,
  EXP_ISGT,
  EXP_ISLTEQ,
  EXP_ISGTEQ,
  EXP_ADD,
  EXP_SUB,
  EXP_OR,
  EXP_MUL,
  EXP_DIV,
  EXP_MOD,
  EXP_LSL,
  EXP_ASR,
  EXP_LSR,
  EXP_AND,
  EXP_NOT,
  EXP_PLUS,
  EXP_MINUS,
  EXP_CONST,
  EXP_VAR
} exp_type;

struct exp_node_ {
  exp_type type;
  union {
    struct {
      exp_node *_0;
      exp_node *_1;
    } _2;
    struct {
      exp_node *_0;
    } _1;
    zinc_word constval;
    name_info *var;
  } val;
};

#endif /* _EXPRESS_H_ */
