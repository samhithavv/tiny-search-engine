# Makefile for indexer directory
# Samhitha Vallury
# Github: samhithavv

# Directories
C = ../common
L = ../libcs50

# compilation 
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$C


COMMON_OBJS = ../libcs50/webpage.o ../libcs50/bag.o ../libcs50/mem.o \
       ../libcs50/hashtable.o ../libcs50/set.o ../libcs50/counters.o \
       ../libcs50/hash.o ../libcs50/file.o ../common/pagedir.o \
       ../common/index.o ../common/word.o

# library dependencies
LLIBS = $(C)/common.a $(L)/libcs50.a

all: indexer indextest

# build indexer 
indexer: indexer.o $(COMMON_OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

# build indextest 
indextest: indextest.o $(COMMON_OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@


$(C)/common.a:
	make -C $(C)

$(L)/libcs50.a:
	make -C $(L)

.PHONY: all test clean 

#runs testing.sh
test: testing.sh indexer
	./testing.sh 

# Clean rule
clean:
	rm -f *.o
	rm -f indexer indextest
	rm -rf *.dSYM
