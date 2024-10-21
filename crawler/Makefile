# Makefile for crawler directory
#
# Samhitha Vallury
# Github: samhithavv


#help from office hours

C = ../common
L = ../libcs50


CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$C
OBJS = crawler.o ../libcs50/webpage.o ../libcs50/bag.o ../libcs50/mem.o ../libcs50/hashtable.o ../libcs50/set.o ../libcs50/counters.o ../libcs50/hash.o ../libcs50/file.o ../common/pagedir.o

LLIBS = $C/common.a $L/libcs50.a 

all: crawler


crawler: $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: all test clean 

../common/pagedir.o: ../common/pagedir.c ../common/pagedir.h
		$(CC) $(CFLAGS) -c ../common/pagedir.c -o ../common/pagedir.o

test:  testing.sh
	./testing.sh > testing.out

clean:
	rm -f *.o
	rm -f crawler
	rm -rf *.dSYM
