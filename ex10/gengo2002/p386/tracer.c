#include <stdio.h>
#include <assert.h>

#include "extern.h"
#include "p386.h"

#include "tracer.h"

static void print_state(void);
static void print_regs(void);

void
tracer(void)
{
  int c;
  int safety;
  int volatile is_breakset;
  u_int32_t breakpoint;
  u_int8_t volatile saved_inst;

  p386_reset();

  safety = 1000;

  is_breakset = 0;

re_setj:

  if (setjmp(p386_jmpbuf_int3))
    {
      if (is_breakset != 0)
        {
          p386_text[breakpoint] = saved_inst;
          is_breakset = 0;
          goto re_setj;
        }
      else
        {
          fprintf(stderr, "unexpected break\n");
          exit(1);
        }
    }

  for (;;)
    {
      print_regs();

      c = getchar();

      switch(c)
        {
        case EOF:
          goto quit;
        case 'q':
          goto quit;
        case 's':
          if (p386_step() != 0)
            goto quit;
          break;
        case 'g':
          p386_run();
          goto quit;
        case 'b':
          if (is_breakset == 1)
            p386_text[breakpoint] = saved_inst;
          scanf("%x", &breakpoint);
          saved_inst = p386_text[breakpoint];
          p386_text[breakpoint] = 0xcc;
          is_breakset = 1;
          printf("breakpoint set to %#x\n", breakpoint);
          break;
        case 'c':
          if (is_breakset == 1)
            {
              p386_text[breakpoint] = saved_inst;
              is_breakset = 0;
              printf("breakpoint cleared\n");
            }
          else
            printf("breakpoint have not set\n");
          break;
        default:
          printf("\n--- [s]tep [g]o [b]reakpoint [c]lear [q]uit ---\n\n");
          break;
        }
      while (c != '\n')
        c = getchar();
    }

quit:

  print_state();

  exit(0);
}

static void
print_regs(void)
{
  fprintf(stderr, "EAX:%08x EBX:%08x ECX:%08x EDX:%08x\n", p386_EAX, p386_EBX, p386_ECX, p386_EDX);
  fprintf(stderr, "EBP:%08x ESP:%08x EIP:%08x ", p386_EBP, p386_ESP, p386_EIP);

  if (p386_EFLAGS & 0x00000040UL)
    fprintf(stderr, "Zero:TRUE ");
  else
    fprintf(stderr, "Zero:FALSE ");

  if (p386_EFLAGS & 0x00000080UL)
    fprintf(stderr, "Sign:TRUE ");
  else
    fprintf(stderr, "Sign:FALSE ");

  if (p386_EFLAGS & 0x00000800UL)
    fprintf(stderr, "OverFlow:TRUE");
  else
    fprintf(stderr, "OverFlow:FALSE");

  fprintf(stderr, "\n[EIP]:%02x\n", 255 & p386_text[p386_EIP - P386_TEXT_START]);
}

static void
print_state(void)
{
  switch (p386_state)
    {
    case P386_STATE_INIT:
      printf("INIT\n");
      break;
    case P386_STATE_RUNNING:
      printf("RUNNING\n");
      break;
    case P386_STATE_INT:
      printf("INT\n");
      break;
    case P386_STATE_UNKINT:
      printf("UNKINT\n");
      break;
    case P386_STATE_ILINST:
      printf("ILINST\n");
      break;
    case P386_STATE_HALT:
      printf("HALT\n");
      break;
    case P386_STATE_UNSRPT:
      printf("UNSRPT\n");
      break;
    default:
      assert(0);
    }
}
