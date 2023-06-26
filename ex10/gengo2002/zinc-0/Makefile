CC = gcc
RM = rm -f

#CFLAGS = -DZINC_FreeBSD -g -ggdb -W -Wall -pedantic -O3
CFLAGS = -g -ggdb -W -Wall -pedantic -O3

OBJS = codegen.o labelgen.o lex.o main.o name.o parse.o token.o

znc : $(OBJS)
	$(CC) -o $@ $(OBJS)

clean :
	$(RM) __rm_food__ *.o
