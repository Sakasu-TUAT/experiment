#include "confdef.h"

#include "token.h"

/* 1 バイトのトークン */
static token one_byte_token[256];

/* その他のスタティックなトークン */
static token const token_eof        =  {LEXVAL_eof,       {0}};
static token const token_coloneq    =  {LEXVAL_coloneq,   {0}};
static token const token_eqeq       =  {LEXVAL_eqeq,      {0}};
static token const token_bangeq     =  {LEXVAL_bangeq,    {0}};
static token const token_lt_or_eq   =  {LEXVAL_lt_or_eq,  {0}};
static token const token_gt_or_eq   =  {LEXVAL_gt_or_eq,  {0}};
static token const token_lsl        =  {LEXVAL_lsl,       {0}};
static token const token_lsr        =  {LEXVAL_lsr,       {0}};
static token const token_asr        =  {LEXVAL_asr,       {0}};

static token const token_IF         =  {LEXVAL_IF,        {0}};
static token const token_WHILE      =  {LEXVAL_WHILE,     {0}};
static token const token_PROC       =  {LEXVAL_PROC,      {0}};
static token const token_WORD       =  {LEXVAL_WORD,      {0}};
static token const token_GETCHAR    =  {LEXVAL_GETCHAR,   {0}};
static token const token_PUTCHAR    =  {LEXVAL_PUTCHAR,   {0}};
static token const token_SET        =  {LEXVAL_SET,       {0}};
static token const token_DEFPROC    =  {LEXVAL_DEFPROC,   {0}};
static token const token_CALL       =  {LEXVAL_CALL,      {0}};

/* 初期化 */
void
init_token(void)
{
  int i;

  for (i = 0; i < 256; i++)
    {
      one_byte_token[i].lex = i;
      one_byte_token[i].sem.w = 0;
    }
}

token const
get_token(lexval lv)
{
  if (lv < 256)
    {
      return one_byte_token[lv];
    }
  else
    {
      switch (lv)
        {
        case LEXVAL_eof:
          return token_eof;
        case LEXVAL_coloneq:
          return token_coloneq;
        case LEXVAL_eqeq:
          return token_eqeq;
        case LEXVAL_bangeq:
          return token_bangeq;
        case LEXVAL_lt_or_eq:
          return token_lt_or_eq;
        case LEXVAL_gt_or_eq:
          return token_gt_or_eq;
        case LEXVAL_lsl:
          return token_lsl;
        case LEXVAL_lsr:
          return token_lsr;
        case LEXVAL_asr:
          return token_asr;

        case LEXVAL_IF:
          return token_IF;
        case LEXVAL_WHILE:
          return token_WHILE;
        case LEXVAL_PROC:
          return token_PROC;
        case LEXVAL_WORD:
          return token_WORD;
        case LEXVAL_GETCHAR:
          return token_GETCHAR;
        case LEXVAL_PUTCHAR:
          return token_PUTCHAR;
        case LEXVAL_SET:
          return token_SET;
        case LEXVAL_DEFPROC:
          return token_DEFPROC;
        case LEXVAL_CALL:
          return token_CALL;

        default:
          EMSTOP("unknown token", 0);
          exit(1);
        }
    }
}

token const
get_token_literal(zinc_word w)
{
  token newtoken;

  newtoken.lex = LEXVAL_literal;
  newtoken.sem.w = w;

  return newtoken;
}

token const
get_token_p(lexval lv, void *p)
{
  token newtoken;

  newtoken.lex = lv;
  newtoken.sem.p = p;

  return newtoken;
}
