#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "confdef.h"
#include "lang_dep.h"

#include "token.h"

#include "lex.h"

/* ʸ����Ȼ����ͤ��б��Τ���ι�¤�� */
typedef struct words_tbl {
  char const *str;
  lexval const lexval;
} words_tbl;

static int get_character(void);
static void unget_character(int c);

static token const lexbang(int c);
static token const lexsl(int c);
static token const lexdec(int c);
static token const lexcolon(int c);
static token const lexlt(int c);
static token const lexeq(int c);
static token const lexgt(int c);
static token const lexname(int c);

static int line_count;
static FILE *in_file;

/* ͽ����ʸ����Ȼ����ͤ��б�����ʬ�����Τ��Ἥ�����ݤĤ��� */
static words_tbl const keywords_tbl[] = {
  {"call",     LEXVAL_CALL},
  {"defproc",  LEXVAL_DEFPROC},
  {"getchar",  LEXVAL_GETCHAR},
  {"if",       LEXVAL_IF},
  {"proc",     LEXVAL_PROC},
  {"putchar",  LEXVAL_PUTCHAR},
  {"set",      LEXVAL_SET},
  {"while",    LEXVAL_WHILE},
  {"word",     LEXVAL_WORD}
};

void
init_lex(FILE *fp)
{
  line_count = 1;
  in_file = fp;
}

static int
get_character(void)
{
  int c;

  c = getc(in_file);

  if (c == '\n')
    line_count++;

  c = ((c == EOF) ? (-1) : (c));

  return c;
}

static void
unget_character(int c)
{
  if (c == EOF)
    return;

  if (c == '\n')
    line_count--;

  ungetc(c, in_file);
}

int
get_linenum(void)
{
  return line_count;
}

token const
lex(void)
{
  int c;

  for (;;)  /* �ȡ������ 1 ʸ���� ( �θ��� ) �򸫤� */
    {
      c = get_character();
      switch (c)
        {
        /* End Of File */
        case -1:
          return get_token(LEXVAL_eof);

        /* ������ɤ����Ф� */

        case '\t':  /* FALLTHRU */  /* �����ȴ���פ��Ѷ�Ū�˻Ȥ� case */
        case '\n':  /* FALLTHRU */
        case '\f':  /* FALLTHRU */
        case '\r':  /* FALLTHRU */
        case '\x1a':  /* FALLTHRU */
        case ' ':  /* FALLTHRU */
          break;

        /* �ʲ�������饯����ʬ�� */
        /* �Ȥ��ʤ�����饯���ˤĤ��Ƥ� case ��񤫤��� default ����Ȥ� */
        /* '_' �򥢥�ե��٥åȤΰ��Ȥߤʤ����Ȥ� */
        /* '/' ���ü�ʰ��� ("//" �ˤ�륳���Ȥ��ɤ����Ф� ) �����  */

        /* 1 ʸ���Ƿ��ꤹ�뵭���� (ASCII �� ) */
        case '%':  /* FALLTHRU */
        case '&':  /* FALLTHRU */
        case '(':  /* FALLTHRU */
        case ')':  /* FALLTHRU */
        case '*':  /* FALLTHRU */
        case '+':  /* FALLTHRU */
        case ',':  /* FALLTHRU */
        case '-':  /* FALLTHRU */
        case ';':  /* FALLTHRU */
        case '{':  /* FALLTHRU */
        case '|':  /* FALLTHRU */
        case '}':  /* FALLTHRU */
        case '~':  /* FALLTHRU */
          return get_token(c);

        /* ʣ��ʸ���ε����� (ASCII �� ) */
        /* (c ���Ϥ��Ƥ��뤬���ۤ�̵��̣�Ǥ��� ) */
        case '!':
          return lexbang(c);

        case '/':
          return lexsl(c);

        case ':':
          return lexcolon(c);

        case '<':
          return lexlt(c);

        case '=':
          return lexeq(c);

        case '>':
          return lexgt(c);

        /* �Ĥ�ϥ���ե��٥åȤȿ���������ˤ���ʳ��ʤ饨�顼 */
        default:
          if (isalpha(c) || (c == '_'))
            {
              return lexname(c);
            }
          else if (c == '0')
            {
              int next;
              next = get_character();
              if (isdigit(next))
                {
                  EMSTOP("decimal literal cannot begin with \'0\' except for 0 itself", line_count);
                  exit(1);
                }
              else
                {
                  unget_character(next);
                  return lexdec(c);
                }
            }
          else if (isdigit(c))
            {
              return lexdec(c);
            }
          else
            {
              EMSTOP("unknown character", line_count);
              exit(1);
            }
        }
    }
}

static token const
lexbang(int c)
{
  int next;

  next = get_character();
  if (next == '=')
    {
      return get_token(LEXVAL_bangeq);
    }
  else
    {
      EMSTOP("unknown operator \'!\'", line_count);
      exit(1);
    }
}

static token const
lexsl(int c)
{
  int next;

  next = get_character();
  if (next == '/')
    {
      do
        next = get_character();
      while (next != '\n');
      return lex();
    }
  else
    {
      unget_character(next);
      return get_token(c);
    }
}

static token const
lexdec(int c)
{
  char buf[2];
  zinc_u_word d;

  d = 0;

  for (;;)
    {
      buf[0] = c;
      buf[1] = '\0';
      d += strtoul(buf, 0, 10);

      c = get_character();

      if (!isdigit(c))
        {
          unget_character(c);
          break;
        }
      if (d > (ZINC_WORD_MAX / 5))  /* XXX ����Ƚ��ϸ�̩�ǤϤʤ� */
        {
          fprintf(stderr, "lex.c : lexdec() : "
                          "overflow (literal of decimal) in line %d\n", line_count);
          exit(1);
        }
      d *= 10;
    }

  /* printf("%d\n", d); */

  return get_token_literal(d);
}

static token const
lexcolon(int c)
{
  int next;

  next = get_character();
  if (next == '=')
    {
      return get_token(LEXVAL_coloneq);
    }
  else
    {
      unget_character(next);
      return get_token(c);
    }
}

static token const
lexlt(int c)
{
  int next;

  next = get_character();
  if (next == '=')
    {
      return get_token(LEXVAL_lt_or_eq);
    }
  else if (next == '<')
    {
      return get_token(LEXVAL_lsl);
    }
  else
    {
      unget_character(next);
      return get_token(c);
    }
}

static token const
lexeq(int c)
{
  int next;

  next = get_character();
  if (next == '=')
    {
      return get_token(LEXVAL_eqeq);
    }
  else
    {
      EMSTOP("unknown operator \'=\'", line_count);
      exit(1);
    }
}

static token const
lexgt(int c)
{
  int next;

  next = get_character();
  if (next == '=')
    {
      return get_token(LEXVAL_gt_or_eq);
    }
  else if (next == '>')
    {
      next = get_character();
      if (next == '>')
        {
          return get_token(LEXVAL_lsr);
        }
      else
        {
          unget_character(next);
          return get_token(LEXVAL_asr);
        }
    }
  else
    {
      unget_character(next);
      return get_token(c);
    }
}

static token const
lexname(int c)
{
  char buf[ZINC_C_NAME_MAX_LEN + 1];

  /* ̾���������ɤ߹��� */
  {
    int i;

    i = 0;
    do
      {
        buf[i++] = c;
        if (i >= ZINC_C_NAME_MAX_LEN)
          {
            EMSTOP("too long name", line_count);
            exit(1);
          }
        c = get_character();
      }
    while (isalnum(c) || (c == '_'));

    buf[i] = '\0';
    unget_character(c);
  }

  /* ͽ��줫�ɤ��������å� */
  {
    int dn = (sizeof(keywords_tbl)) / (sizeof(keywords_tbl[0])) - 1;
    int up = 0;  /* 2 ʬ�����ξ峦�Ȳ��� */
    int mid;
    int r;

    for(;;)
      {
        mid = (dn + up) / 2;
        r = strcmp(buf, keywords_tbl[mid].str);

        if (r == 0)  /* ͽ��줬���Ĥ��ä� */
          return get_token(keywords_tbl[mid].lexval);
        else if (dn <= up)  /* ���Ĥ���ʤ� */
          {
            char *name;

            name = malloc(1 + strlen(buf));
            strcpy(name, buf);
            return get_token_p(LEXVAL_name, name);
          }
        else if (r < 0)
          dn = mid - 1;
        else if (r > 0)
          up = mid + 1;
      }

    /* NOTREACHED */
  }
}
