#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "extern.h"

#define MEM_RESOLV(addr) \
  ((u_int32_t *)( \
   (((P386_STACK_START - 1UL) - ((u_int32_t)(addr))) <= P386_STACK_LIMIT) \
   ? (p386_stack + ((u_int32_t)(addr)) - (P386_STACK_START - P386_STACK_SIZE)) \
   : ( \
      ((((u_int32_t)(addr)) - P386_DATA_START) <= P386_DATA_LIMIT) \
      ? (p386_data + ((u_int32_t)(addr)) - P386_DATA_START) \
      : ((void *)0) \
     ) \
  ))

int
main(void)
{
  printf("text:%8p\n", p386_text);
  printf("data:%8p\n", p386_data);
  printf("stack:%8p\n", p386_stack);
  printf("\n");
  printf("0x40000000: %8p\n", MEM_RESOLV(0x40000000UL));
  printf("0x4000ffff: %8p\n", MEM_RESOLV(0x4000ffffUL));
  printf("0xbfffffff: %8p\n", MEM_RESOLV(0xbfffffffUL));
  printf("0xbfff0000: %8p\n", MEM_RESOLV(0xbfff0000UL));
  printf("0x3fffffff: %8p\n", MEM_RESOLV(0x3fffffffUL));
  printf("0x40010000: %8p\n", MEM_RESOLV(0x40010000UL));
  printf("0xc0000000: %8p\n", MEM_RESOLV(0xc0000000UL));
  printf("0xbffeffff: %8p\n", MEM_RESOLV(0xbffeffffUL));

  exit(0);
}
