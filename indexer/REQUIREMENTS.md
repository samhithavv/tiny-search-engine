# CS50 TSE - Index Requirements
## Samhitha Vallury - github: samhithavv

The TSE indexer is a standalone program that reads the document files produced by the TSE crawler, builds an index, and writes that index to a file. Its companion, the index tester, loads an index file produced by the indexer and saves it to another file.

Indexer:
The indexer shall: execute from a command line with usage syntax: ./indexer pageDirectory indexFilename
where pageDirectory is the pathname of a directory produced by the Crawler, and
where indexFilename is the pathname of a file into which the index should be written; the indexer creates the file (if needed) and overwrites the file (if it already exists).

pageDirectory is the pathname for a directory produced by the Crawler, and
indexFilename is the pathname of a file that can be written;
read documents from the pageDirectory, each of which has a unique document ID, wherein

Builds an inverted-index data structure mapping from words to (documentID, count) pairs, wherein each count represents the number of occurrences of the given word in the given document. Ignore words with fewer than three characters, and "normalize" the word before indexing. (Here, "normalize" means to convert all letters to lower-case.)


Index Tester:
The index tester shall:

execute from a command line with usage syntax
./indextest oldIndexFilename newIndexFilename
where oldIndexFilename is the name of a file produced by the indexer, and
where newIndexFilename is the name of a file into which the index should be written.
load the index from the oldIndexFilename into an inverted-index data structure.
create a file newIndexFilename and write the index to that file, in the format described below.

