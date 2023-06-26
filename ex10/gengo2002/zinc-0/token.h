#if !defined _TOKEN_H_
#define _TOKEN_H_

#include "lang_dep.h"

typedef struct token {
  int lex;  /* ������ : 1 �Х��Ȥ���ʤ�ȡ����� ( ̾������� ) �� */
              /* ����ʸ�������ɤ�ľ������ */
  union {
    void *p;
    zinc_word w;
  } sem;  /* ��̣�� : Ŭ���ʾ���ؤΥݥ��� */
} token;

/*
ʣ���Х��Ȥ���ʤ�ȡ����� ( ̾���� 1 �Х��Ȥξ���ޤ� ) �ʤɤλ����͡�
1 �Х��Ȥ���ʤ�ȡ�����Ⱦ��ͤ��� 0 �� 255 �϶����Ƥ����ͤФʤ�ʤ���
*/
typedef enum lexval {
  LEXVAL_eof = 257,  /* End Of File */
  LEXVAL_name,       /* ̾�� ( ͽ������ ) */
  LEXVAL_literal,    /* ( ����Ū�� ) ��ƥ�� */
  LEXVAL_coloneq,    /* := */
  LEXVAL_eqeq,       /* == */
  LEXVAL_bangeq,     /* != */
  LEXVAL_lt_or_eq,   /* <= */
  LEXVAL_gt_or_eq,   /* >= */
  LEXVAL_lsl,        /* << */
  LEXVAL_asr,        /* >> */
  LEXVAL_lsr,        /* >>> */

  LEXVAL_IF = 513,  /* ������ͽ��� */
  LEXVAL_WHILE,
  LEXVAL_PROC,
  LEXVAL_WORD,
  LEXVAL_GETCHAR,
  LEXVAL_PUTCHAR,
  LEXVAL_SET,
  LEXVAL_DEFPROC,
  LEXVAL_CALL
} lexval;

void init_token(void);
token const get_token(lexval lv);
token const get_token_literal(zinc_word w);
token const get_token_p(lexval lv, void *p);

#endif /* _TOKEN_H_ */
