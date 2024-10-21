# CS50 TSE - Crawler Implementation
## Samhitha Vallury - github: samhithavv

The Crawler is implemented in one file crawler.c, with four functions.

main
The main function simply calls parseArgs and crawl, then exits zero.

parseArgs
Given arguments from the command line, extract them into the function parameters; return only if successful.

for seedURL, normalize the URL and validate it is an internal URL
for pageDirectory, call pagedir_init()
for maxDepth, ensure it is an integer in specified range
if any trouble is found, print an error to stderr and exit non-zero.

crawl
Do the real work of crawling from seedURL to maxDepth and saving pages in pageDirectory

pageScan
This function implements the pagescanner mentioned in the design. Given a webpage, scan the given page to extract any links (URLs), ignoring non-internal URLs; for any URL not already seen before (i.e., not in the hashtable), add the URL to both the hashtable pages_seen and to the bag pages_to_crawl