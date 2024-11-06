# CS50 TSE - Querier Requirements
## Samhitha Vallury - github: samhithavv

The TSE Querier is a standalone program that reads the index file produced by the TSE Indexer, and page files produced by the TSE Querier, and answers search queries submitted via stdin.

The querier shall:

execute from a command line with usage syntax

./querier pageDirectory indexFilename
where pageDirectory is the pathname of a directory produced by the Crawler, and
where indexFilename is the pathname of a file produced by the Indexer.
validate it received exactly two command-line arguments and that

pageDirectory is the pathname for a directory produced by the Crawler, and
indexFilename is the pathname of a file that can be read;
load the index from indexFilename into an internal data structure.

read search queries from stdin, one per line, until EOF.

clean and parse each query according to the syntax described below.
if the query syntax is somehow invalid, print an error message, do not perform the query, and prompt for the next query.
print the 'clean' query for user to see.
use the index to identify the set of documents that satisfy the query, as described below.
if the query is empty (no words), print nothing.
if no documents satisfy the query, print No documents match.
otherwise, rank the resulting set of documents according to its score, as described below, and print the set of documents in decreasing rank order; for each, list the score, document ID and URL. (Obtain the URL by reading the first line of the relevant document file from the pageDirectory.)
output nothing to stdout other than what is indicated above

exit zero when EOF is reached on stdin; exit with an error message to stderr and non-zero exit status on encountering an unrecoverable error, including

out of memory,
invalid command-line arguments,
unable to read a file named pageDirectory/.crawler,
unable to read a file named pageDirectory/1
unable to read a file named indexFilename
The querier may assume that

pageDirectory has files named 1, 2, 3, ..., without gaps.
The content of files in pageDirectory follow the format as defined in the specs; thus your code (to read the files) need not have extensive error checking.
The content of the file named by indexFilename follows our index file format (as defined in Lab 5); thus your code (to recreate an index structure by reading a file) need not have extensive error checking.
The provided index file corresponds to the provided pageDirectory, that is, was built by indexer from the files in that directory.
