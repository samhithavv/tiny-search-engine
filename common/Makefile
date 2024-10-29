# Makefile for common directory

# Samhitha Vallury 
# Github - samhithavv

# help from office hours

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../libcs50
LLIBS = ../libcs50/libcs50-given.a 
LIB = common.a

# relevant objects
OBJS = pagedir.o index.o word.o

all: $(LIB)

$(LIB): $(OBJS) $(LLIBS)
	ar cr $(LIB) $(LLIBS) $(OBJS)

pagedir: $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

# Pattern rule to compile .o files from .c files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: test valgrind clean

# Makes clean and removes unnecessary files
clean:
	rm -f core
	rm -f $(LIB) *~ *.o
