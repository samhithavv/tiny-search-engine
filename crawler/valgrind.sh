#!/bin/bash

#same as testing file, can comment and un-comment to reduce time for running


#valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters_test 5

valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html  toscrape_test 1

# valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html  wiki_test 1
