CC = gcc
RM = rm -f

CFLAGS = -g -ggdb -W -Wall -pedantic -O3

OBJS = global.o main.o p386.o tracer.o

p386 : $(OBJS)
	$(CC) -o $@ $(OBJS)

clean :
	$(RM) __rm_food__ *.o
