# CS50 TSE - Index Design
## Samhitha Vallury - github: samhithavv

Based on instructions: 

Inputs and outputs
Input: the indexer reads files from a directory by constructing file pathnames from the pageDirectory parameter followed by a numeric document ID (as described in the Requirements).

The indexer reads document files in sequential ID order, beginning at 1, until is unable to open one of those files.

Output: We save the index to a file using the format described in the Requirements.

Functional decomposition into modules
We anticipate the following modules or functions:

main, which parses arguments and initializes other modules;
indexBuild, which builds an in-memory index from webpage files it finds in the pageDirectory;
indexPage, which scans a webpage document to add its words to the index.
And some helper modules that provide data structures:

index, a module providing the data structure to represent the in-memory index, and functions to read and write index files;
webpage, a module providing the data structure to represent webpages, and to scan a webpage for words;
pagedir, a module providing functions to load webpages from files in the pageDirectory;
word, a module providing a function to normalize a word.
