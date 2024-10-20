# Makefile for CS50 library
#   Builds and compiles all these utility functions into a library.
#
# David Kotz, April 2016, July 2017, April 2019, 2021
# updated by Xia Zhou, July 2016

# object files, and the target library

C = ../common
L = ../libcs50


CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$C
OBJS = crawler.o ../libcs50/webpage.o ../libcs50/bag.o ../libcs50/mem.o ../libcs50/hashtable.o ../libcs50/set.o ../libcs50/counters.o ../libcs50/hash.o ../libcs50/file.o ../common/pagedir.o


LLIBS = $C/common.a $L/libcs50.a 


all: crawler

#MAKE = make

crawler: $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: all test clean 

../common/pagedir.o: ../common/pagedir.c ../common/pagedir.h
		$(CC) $(CFLAGS) -c ../common/pagedir.c -o ../common/pagedir.o

# Build $(LIB) by archiving object files
# (you will need to drop in copy of set.c, counters.c, hashtable.c)

# bag.o: ../libcs50/bag.h
# counters.o: ../libcs50/counters.h
# file.o: ../libcs50/file.h
# hashtable.o: ../libcs50/hashtable.h ../libcs50/set.h ../libcs50/hash.h 
# hash.o: ../libcs50/hash.h
# mem.o: ../libcs50/mem.h
# set.o: ../libcs50/set.h
# webpage.o:  ../libcs50/webpage.h



# VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

# valgrind: 
# 	$(VALGRIND) ./crawler < testing.out

test:  testing.sh
	./testing.sh > testing.out


# crawler -bash -v
# sourcelist: Makefile *.md *.c *.h
# 	@echo $^

# clean up after our compilation
clean:
	rm -f *.o
	rm -f crawler
	rm -rf *.dSYM
#	rm -f $(OBJS) crawler
	

# rm -f core
# rm -f $(LIB) *~ *.o
# rm -rf *.dSYM  # MacOS debugger info
# rm -f *~ *.o
# rm -f hashtabletest
# rm -f core
