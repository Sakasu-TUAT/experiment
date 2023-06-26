#if !defined _TOKEN_H_
#define _TOKEN_H_

#include "lang_dep.h"

typedef struct token {
  int lex;  /* 字句値 : 1 バイトからなるトークン ( 名前を除く ) の */
              /* 場合は文字コードが直接入る */
  union {
    void *p;
    zinc_word w;
  } sem;  /* 意味値 : 適当な情報へのポインタ */
} token;

/*
複数バイトからなるトークン ( 名前は 1 バイトの場合も含む ) などの字句値。
1 バイトからなるトークンと衝突する 0 〜 255 は空けておかねばならない。
*/
typedef enum lexval {
  LEXVAL_eof = 257,  /* End Of File */
  LEXVAL_name,       /* 名前 ( 予約語除く ) */
  LEXVAL_literal,    /* ( 字句的に ) リテラル */
  LEXVAL_coloneq,    /* := */
  LEXVAL_eqeq,       /* == */
  LEXVAL_bangeq,     /* != */
  LEXVAL_lt_or_eq,   /* <= */
  LEXVAL_gt_or_eq,   /* >= */
  LEXVAL_lsl,        /* << */
  LEXVAL_asr,        /* >> */
  LEXVAL_lsr,        /* >>> */

  LEXVAL_IF = 513,  /* これより予約語 */
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
