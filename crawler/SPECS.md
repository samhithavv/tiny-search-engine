# CS50 TSE - Crawler Specs
## Samhitha Vallury - github: samhithavv

1. execute from a command line with usage syntax ./crawler seedURL pageDirectory maxDepth
2. mark the pageDirectory as a 'directory produced by the Crawler' by creating a file named .crawler in that directory.
3. crawl all "internal" pages reachable from seedURL, following links to a maximum depth of maxDepth; where maxDepth=0 means that crawler only explores the page at seedURL, and maxDepth=1 means that crawler only explores the page at seedURL and those pages to which seedURL links, and so forth inductively.
4. print nothing to stdout, other than logging its progress; see an example format in the knowledge unit. Write each explored page to the pageDirectory with a unique document ID
5. exit zero if successful; exit with an error message to stderr and non-zero exit status if it encounters an unrecoverable error