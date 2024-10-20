#!/bin/bash

# Set directories for testing
LETTERS_DIR="letters_test"
TOSCRAPE_DIR="toscrape_test"
WIKI_DIR="wiki_test"

# Remove old directories and create fresh ones
rm -rf $LETTERS_DIR $TOSCRAPE_DIR $WIKI_DIR
mkdir $LETTERS_DIR $TOSCRAPE_DIR $WIKI_DIR

# need to add boundary cases and erroneous arguments!!!!!

# 1. Erroneous Arguments Testing 
#./crawler #print usage
#./crawler invalidURL $LETTERS_DIR 1 #exit and display url error message
#./crawler http://cs50tse.cs.dartmouth.edu/tse/letters $LETTERS_DIR invalidDepth #exit and display maxdepth message
#./crawler http://cs50tse.cs.dartmouth.edu/tse/letters nonExistentDir 1 #exit and display dir error message

# 2. Valgrind test on 'toscrape' website with depth 1
#valgrind --leak-check=full --show-leak-kinds=all ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape $TOSCRAPE_DIR 1

# Depths 0, 1, 2, and 10 should work correctly for the letters website.
# Depths 0, 1, 2, and 3 are tested for the toscrape website.
# Depths 0, 1, and 2 are tested for the wikipedia website.

#./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ $LETTERS_DIR 10 
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html $LETTERS_DIR 1
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters $LETTERS_DIR 2
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters $LETTERS_DIR 10

# ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape $TOSCRAPE_DIR 0
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape $TOSCRAPE_DIR 1
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape $TOSCRAPE_DIR 2
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape $TOSCRAPE_DIR 3

# ./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia $WIKI_DIR 0
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia $WIKI_DIR 3
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia $WIKI_DIR 2



# We've established a 'playground' for CS50 crawlers to explore.

# A sampling of tests that should be run:

# Test the program with various forms of incorrect command-line arguments to ensure that its command-line parsing, and validation of those parameters, works correctly.

# Crawl a simple, closed set of cross-linked web pages like letters, at depths 0, 1, 2, or more. Verify that the files created match expectations.

# Repeat with a different seed page in that same site. If the site is indeed a graph, with cycles, there should be several interesting starting points.

# Point the crawler at one of our bigger playgrounds. Explore at depths 0, 1, 2, from various starting pages. (It takes a long time to run at depth 2 or higher!) Verify that the files created match expectations.

# When you are confident that your crawler runs well, test it with a greater depth - but be ready to kill it if it seems to be running amok.

# # Verify files
# ls $LETTERS_DIR
# ls $TOSCRAPE_DIR
# ls $WIKI_DIR
