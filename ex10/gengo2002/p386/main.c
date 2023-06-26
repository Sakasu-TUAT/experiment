#include <stdlib.h>
#include <stdio.h>
#include "extern.h"
#include "tracer.h"


int
main(int argc, char *argv[])
{
  FILE *fp;
  int x, i;

  if (argc != 2)
    {
      fprintf(stderr, "usage: p386 <inputfile>\n");
      exit(1);
    }

  if ((fp = fopen(argv[1], "r")) == 0)
    {
      perror((void *)0);
      exit(1);
    }

  i = 0;

  while(fscanf(fp, "%x", &x) == 1)
    p386_text[i++] = x;

  tracer();

  exit(0);
}
