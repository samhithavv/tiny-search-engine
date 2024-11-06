#!/bin/bash
#Samhitha Vallury - github: samhithavv
#testing file

#error test - error for pagedirectory
echo pageDirectory check
./querier fakePageDirectory ~/cs50-dev/shared/tse/output/toscrape-2.index

#error test - error for indexFile
echo indexFile check
./querier ~/cs50-dev/shared/tse/output/toscrape-2 badIndexFile


#usage test
echo usage check
./querier 

#usage test
echo usage check
./querier ~/cs50-dev/shared/tse/output/toscrape-2 badIndexFile ~/cs50-dev/shared/tse/output/toscrape-2 badIndexFile

#correct test
echo querier test
./querier ~/cs50-dev/shared/tse/output/toscrape-2 ~/cs50-dev/shared/tse/output/toscrape-2.index

echo valgrind for querier
valgrind --leak-check=full --show-leak-kinds=all  ./querier ~/cs50-dev/shared/tse/output/toscrape-2 ~/cs50-dev/shared/tse/output/toscrape-2.index
echo 

echo fuzz test 1
./fuzzquery ~/cs50-dev/shared/tse/output/toscrape-2.index 5 0 | ./querier ~/cs50-dev/shared/tse/output/toscrape-2 ~/cs50-dev/shared/tse/output/toscrape-2.index
echo



