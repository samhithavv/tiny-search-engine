# Makefile for common directory

#Samhitha Vallury 
#Github - samhithavv

#help from office hours

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../libcs50
LLIBS = ../libcs50/libcs50-given.a 
LIB = common.a

#relevant objects
OBJS = pagedir.o 

all: $(LIB)


$(LIB): $(OBJS) $(LLIBS)
	ar cr $(LIB) $(LLIBS) $(OBJS)

pagedir: $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

#dependency
pagedir.o: pagedir.h


.PHONY: test valgrind clean

#makes clean and removes unecessary files
clean:
	rm -f core
	rm -f $(LIB) *~ *.o
