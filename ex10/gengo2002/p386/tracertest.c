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

  p386_text[0] = 0xe8;
  p386_text[1] = 0x01;
  p386_text[2] = 0x00;
  p386_text[3] = 0x00;
  p386_text[4] = 0x00;
  p386_text[5] = 0xf4;

  p386_text[6] = 0x55;
  p386_text[7] = 0x89;
  p386_text[8] = 0xe5;
  p386_text[9] = 0x83;
  p386_text[10] = 0xec;
  p386_text[11] = 0x04;
  p386_text[12] = 0xc7;
  p386_text[13] = 0xc0;
  p386_text[14] = 0x00;
  p386_text[15] = 0x00;
  p386_text[16] = 0x00;
  p386_text[17] = 0x00;
  p386_text[18] = 0x89;
  p386_text[19] = 0x45;
  p386_text[20] = 0xfc;
  p386_text[21] = 0xc7;
  p386_text[22] = 0xc0;
  p386_text[23] = 0x09;
  p386_text[24] = 0x00;
  p386_text[25] = 0x00;
  p386_text[26] = 0x00;
  p386_text[27] = 0x50;
  p386_text[28] = 0x8b;
  p386_text[29] = 0x45;
  p386_text[30] = 0xfc;
  p386_text[31] = 0x59;
  p386_text[32] = 0x39;
  p386_text[33] = 0xc8;
  p386_text[34] = 0xc7;
  p386_text[35] = 0xc0;
  p386_text[36] = 0x00;
  p386_text[37] = 0x00;
  p386_text[38] = 0x00;
  p386_text[39] = 0x00;
  p386_text[40] = 0x7f;
  p386_text[41] = 0x02;
  p386_text[42] = 0xf7;
  p386_text[43] = 0xd0;
  p386_text[44] = 0x21;
  p386_text[45] = 0xc0;
  p386_text[46] = 0x74;
  p386_text[47] = 0x2c;
  p386_text[48] = 0x8b;
  p386_text[49] = 0x45;
  p386_text[50] = 0xfc;
  p386_text[51] = 0x50;
  p386_text[52] = 0xc7;
  p386_text[53] = 0xc0;
  p386_text[54] = 0x30;
  p386_text[55] = 0x00;
  p386_text[56] = 0x00;
  p386_text[57] = 0x00;
  p386_text[58] = 0x59;
  p386_text[59] = 0x01;
  p386_text[60] = 0xc8;
  p386_text[61] = 0xcd;
  p386_text[62] = 0xc1;
  p386_text[63] = 0xc7;
  p386_text[64] = 0xc0;
  p386_text[65] = 0x20;
  p386_text[66] = 0x00;
  p386_text[67] = 0x00;
  p386_text[68] = 0x00;
  p386_text[69] = 0xcd;
  p386_text[70] = 0xc1;
  p386_text[71] = 0xc7;
  p386_text[72] = 0xc0;
  p386_text[73] = 0x01;
  p386_text[74] = 0x00;
  p386_text[75] = 0x00;
  p386_text[76] = 0x00;
  p386_text[77] = 0x50;
  p386_text[78] = 0x8b;
  p386_text[79] = 0x45;
  p386_text[80] = 0xfc;
  p386_text[81] = 0x59;
  p386_text[82] = 0x01;
  p386_text[83] = 0xc8;
  p386_text[84] = 0x89;
  p386_text[85] = 0x45;
  p386_text[86] = 0xfc;
  p386_text[87] = 0xe9;
  p386_text[88] = 0xb9;
  p386_text[89] = 0xff;
  p386_text[90] = 0xff;
  p386_text[91] = 0xff;
  p386_text[92] = 0xc7;
  p386_text[93] = 0xc0;
  p386_text[94] = 0x0a;
  p386_text[95] = 0x00;
  p386_text[96] = 0x00;
  p386_text[97] = 0x00;
  p386_text[98] = 0xcd;
  p386_text[99] = 0xc1;
  p386_text[100] = 0xc9;
  p386_text[101] = 0xc3;

  p386_reset();

  safety = 1000;

/*
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
*/
  p386_run();

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
