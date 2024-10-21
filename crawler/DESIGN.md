# CS50 TSE - Crawler Design
## Samhitha Vallury - github: samhithavv

Functions:
main, which parses arguments and initializes other modules
crawl, which loops over pages to explore, until the list is exhausted
pagefetcher, which fetches a page from a URL
pagescanner, which extracts URLs from a page and processes each one
pagesaver, which outputs a page to the the appropriate file


Helper modules that provide necessary data structures:

bag of pages we have yet to explore
hashtable of URLs we've seen so far

Also uses webpage, mem, file, and set (through hashtable)