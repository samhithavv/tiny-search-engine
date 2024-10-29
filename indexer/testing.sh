#!/bin/bash



# Case 1: No arguments
echo "Case 1: no args" 
./indexer
echo 
 #should print usage


# Case 2: One argument
echo "Case 2: One argument" #should print usage
./indexer pageDirectory
echo 

# Case 3: Three or more arguments
echo "Case 3: Extra arguments" 
./indexer pageDirectory indexFile extraArgument # usage error message
echo 

# Case 4: Invalid pageDirectory (non-existent path)
echo "Case 4: Invalid pageDirectory (non-existent path)" #print pagedirectory invalid
./indexer invalidPath indexFile
echo 

# Case 5: Invalid pageDirectory (not a crawler directory) - had help from TA
mkdir -p emptyDirectory
echo "Case 5: Invalid pageDirectory (not a crawler directory)"
./indexer emptyDirectory indexFile # should print directory error message
rm -rf emptyDirectory
echo 


# Case 6: Invalid indexFile (non-existent path)  
echo "Case 6: Invalid indexFile (non-existent path)"
./indexer ~/cs50-dev/shared/tse/output/letters-1 nonExistent/nonExistentFile
echo 

# Case 7: Invalid indexFile (read-only directory) 
mkdir -p readonlyDir
chmod -w readonlyDir
echo "Case 7: Invalid indexFile (read-only directory)"
./indexer readonlyDir index.out
rm -rf readonlyDir
echo 

# # Case 8: Valid arguments - run indextest to validate for all three directories

echo "Case 8: Valid arguments"

./indexer ~/cs50-dev/shared/tse/output/toscrape-0 index2.out
./indextest index2.out check2.out
echo 

echo "Case 9: Valid arguments"

./indexer ~/cs50-dev/shared/tse/output/wikipedia-1 index3.out
./indextest index3.out check3.out
echo 

echo "Case 10: Valid arguments"

./indexer ~/cs50-dev/shared/tse/output/letters-3 index.out
./indextest index.out check.out
echo 


echo valgrind for indexer
valgrind --leak-check=full --show-leak-kinds=all  ./indexer ~/cs50-dev/shared/tse/output/letters-1 index.out
echo 


echo valgrind for indextest
valgrind --leak-check=full --show-leak-kinds=all  ./indextest index.out check.out
echo 


if diff index.out check.out; then #checks ouput for letter-3 test
    echo "The files are identical."
else
    echo "Test failed: The files differ."
fi

