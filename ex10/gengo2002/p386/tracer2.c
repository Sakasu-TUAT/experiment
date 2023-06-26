#include <stdio.h>
#include <assert.h>

#include "extern.h"
#include "p386.h"

#include "tracer.h"

static void print_state(void);

void
tracer(void)
{
  int safety;

  p386_text[0] = 0xc7;
  p386_text[1] = 0xc0;
  p386_text[2] = 0x01;
  p386_text[3] = 0x00;
  p386_text[4] = 0xff;
  p386_text[5] = 0xff;
  p386_text[6] = 0xc7;
  p386_text[7] = 0xc1;
  p386_text[8] = 0x00;
  p386_text[9] = 0x00;
  p386_text[10] = 0x01;
  p386_text[11] = 0x00;
  p386_text[12] = 0x99;
  p386_text[13] = 0xf7;
  p386_text[14] = 0xe9;
  p386_text[15] = 0xf4;
  p386_text[16] = 0x01;
  p386_text[17] = 0x00;
  p386_text[18] = 0x00;
  p386_text[19] = 0x00;
  p386_text[20] = 0xd3;
  p386_text[21] = 0xf8;
  p386_text[22] = 0xd3;
  p386_text[23] = 0xf8;
  p386_text[24] = 0xd3;
  p386_text[25] = 0xf8;
  p386_text[26] = 0xd3;
  p386_text[27] = 0xf8;
  p386_text[28] = 0xd3;
  p386_text[29] = 0xf8;
  p386_text[30] = 0xd3;
  p386_text[31] = 0xf8;
  p386_text[32] = 0xd3;
  p386_text[33] = 0xf8;
  p386_text[34] = 0xd3;
  p386_text[35] = 0xf8;
  p386_text[36] = 0xd3;
  p386_text[37] = 0xf8;
  p386_text[38] = 0xf4;

  p386_reset();

  safety = 1000;

  do
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

      fprintf(stderr, "\n[EIP]:%02x\n\n", 255 & p386_text[p386_EIP - P386_TEXT_START]);
    }
  while ((p386_step() == 0) && ((--safety) > 0));

  print_state();

  exit(0);
}

static void
print_state(void)
{
  switch (p386_state)
    {
    case P386_STATE_INIT:
      printf("\nINIT\n");
      break;
    case P386_STATE_RUNNING:
      printf("\nRUNNING\n");
      break;
    case P386_STATE_INT:
      printf("\nINT\n");
      break;
    case P386_STATE_UNKINT:
      printf("\nUNKINT\n");
      break;
    case P386_STATE_ILINST:
      printf("\nILINST\n");
      break;
    case P386_STATE_HALT:
      printf("\nHALT\n");
      break;
    case P386_STATE_UNSRPT:
      printf("\nUNSRPT\n");
      break;
    default:
      assert(0);
    }
}
