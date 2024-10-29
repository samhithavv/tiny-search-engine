# CS50 TSE - Index Implementation
## Samhitha Vallury - github: samhithavv

#based on instructions

Implementation: 

Modules:
Index: hashtable mapping each unique word to a counters_t structure:
    Keys: Unique words from crawler output
    Values: counters_t structures, each mapping docIDs to the count of word in particular document
Webpage, Counters, Hashtable, and Set are also used

Indexer.c 3 functions:

Main
The main function validates input and calls indexBuild, then exits with status zero if successful.

indexBuild
The indexBuild function handles the main indexing process by iterating through document files in the pageDirectory and updating word frequencies.

Pseudocode:
parse the command line, validate parameters, initialize other modules

call indexBuild, with pageDirectory
where indexBuild:
  creates a new 'index' object
  loops over document ID numbers, counting from 1
    loads a webpage from the document file 'pageDirectory/id'
    if successful, 
      passes the webpage and docID to indexPage


Pseudocode:
steps through each word of the webpage,
   skips trivial words (less than length 3),
   normalizes the word (converts to lower case),
   looks up the word in the index,
     adding the word to the index if needed
   increments the count of occurrences of this word in this docID


Error Testing: Ran with invalid arguments to verify error handling.
Memory Testing: Used valgrind with a moderate test case to ensure memory management is robust.

indexRebuild:
Pseudocode:
Open indexFilename for writing.
For each word in the index:
Write the word, followed by each docID: count pair.
Close the file.
index_load: Loads an index file into memory for further use.


If the word exists, update the docID counter.
If the word is new, create a counters entry.


For argument validation:

pageDirectory: Confirmed with pagedir_validate.
indexFilename: Confirmed as writable by attempting to open the file.
Errors in arguments result in messages printed to stderr and a non-zero exit status.

