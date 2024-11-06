# Makefile for querier directory
# Samhitha Vallury
# Github: samhithavv

# Directories
C = ../common
L = ../libcs50

# Compilation 
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L -I$C

# Common object files
COMMON_OBJS = ../libcs50/webpage.o ../libcs50/bag.o ../libcs50/mem.o \
              ../libcs50/hashtable.o ../libcs50/set.o ../libcs50/counters.o \
              ../libcs50/hash.o ../libcs50/file.o ../common/pagedir.o \
              ../common/index.o ../common/word.o 

# Additional object files for the querier
QUERIER_OBJS = querier.o ranking.o iterators.o




# Library dependencies
LLIBS = $(C)/common.a $(L)/libcs50.a

# Targets
all: querier

# Build querier 
querier: $(QUERIER_OBJS) $(COMMON_OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

fuzzquery: fuzzquery.o $(COMMON_OBJS) $(LLIBS)
	$(CC) $(CFLAGS) fuzzquery.o $(COMMON_OBJS) $(LLIBS) -o fuzzquery

fuzzquery.o: fuzzquery.c
	$(CC) $(CFLAGS) -c fuzzquery.c

# Rules for building the common and libcs50 libraries if not built
$(C)/common.a:
	make -C $(C)

$(L)/libcs50.a:
	make -C $(L)

.PHONY: all test clean 

# Run testing script
test: testing.sh querier
	./testing.sh &> testing.out

# Clean rule
clean:
	rm -f *.o
	rm -f querier querier_test
	rm -rf *.dSYM
