#!/bin/bash

#valgrind tests are in valgrind.sh
#due to how long it takes to run with multiple long commands, 
#can comment and un-comment different lines - the current ones are what produced testing.out


# Remove old directories and create fresh ones
rm -rf letters_test toscrape_test wiki_test
mkdir letters_test toscrape_test wiki_test

# erroneous arguments
./crawler #prints usage error
./crawler invalidURL letters_test 1 #exit and display url error message
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters letters_test invalid #exit and display maxdepth message
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters nonExistentDir 1 #exit and display dir error message

#add descriptions for pagedir functions


./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters_test 5
#./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters_test 10
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters_test 2
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html letters_test 10

#  ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html toscrape_test 0
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html  toscrape_test 1
#  ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html  toscrape_test 3

# ./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html  wiki_test 0
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html wiki_test 3
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html  wiki_test 1



