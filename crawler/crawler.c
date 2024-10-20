//Samhitha Vallury, CS50FA24
//Github: samhithavv
//Lab 4 - TSE crawler

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../libcs50/bag.h"
#include "../libcs50/mem.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/set.h"
#include "../libcs50/webpage.h"
#include "../common/pagedir.h"
#include "../libcs50/mem.h"



//ADD NULL CHECKS TO EACH VARIABLE
/*
parse the command line, validate parameters, initialize other modules
add seedURL to the bag of webpages to crawl, marked with depth=0
add seedURL to the hashtable of URLs seen so far
while there are more webpages in the bag:
    extract a webpage (URL,depth) item from the bag
    pause for one second
    use pagefetcher to retrieve a webpage for that URL
    use pagesaver to write the webpage to the pageDirectory with a unique document ID
    if the webpage depth is < maxDepth, explore the webpage to find the links it contains:
      use pagescanner to parse the webpage to extract all its embedded URLs
      for each extracted URL:
        normalize the URL (per requirements spec)
        if that URL is internal (per requirements spec):
          try to insert that URL into the *hashtable* of URLs seen;
            if it was already in the table, do nothing;
            if it was added to the table:
               create a new webpage for that URL, marked with depth+1
               add that new webpage to the bag of webpages to be crawled
*/


/* while there is another URL in the page
	if that URL is Internal,
		insert the webpage into the hashtable
		if that succeeded,
			create a webpage_t for it
			insert the webpage into the bag
	free the URL*/

  
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen) {
    char* url;
    int pos = 0;

    while ((url = webpage_getNextURL(page, &pos)) != NULL) {
        // Normalize the URL
        char* normalizedURL = normalizeURL(url);
        //printf("normalized url: %s\n", webpage_getURL(page)); 

        if (normalizedURL != NULL && isInternalURL(normalizedURL)) {
            // If the URL is internal, insert it into the hashtable
            if (hashtable_insert(pagesSeen, normalizedURL, "")) {
                // If insertion succeeded, create a new webpage_t for it
                webpage_t* newPage = webpage_new(normalizedURL, webpage_getDepth(page) + 1, NULL);

                printf("%d      Found: %s\n", webpage_getDepth(newPage), normalizedURL);
    

                // Insert the new webpage into the bag for future crawling
                if (isInternalURL(normalizedURL)){
                    //printf("boolean: %d\n", isInternalURL(normalizedURL));
                    bag_insert(pagesToCrawl, newPage);
                    printf("%d      Added: %s\n", webpage_getDepth(newPage), normalizedURL);
                } else {
                    printf("%d      IgnExtrn: %s\n", webpage_getDepth(newPage), normalizedURL);
                }
    
            } else {
                // Free the normalized URL if it was not inserted
                free(normalizedURL);
            }
        } else {
            // Free the normalized URL if it is not valid
            free(normalizedURL);
        }

        // Free the original URL extracted from the page
        free(url);
    }
}





/*Given arguments from the command line, extract them into the function parameters; return only if successful.

for seedURL, normalize the URL and validate it is an internal URL
for pageDirectory, call pagedir_init()
for maxDepth, ensure it is an integer in specified range
if any trouble is found, print an error to stderr and exit non-zero.
*/


static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth) {
    char *normalizedURL2 = normalizeURL(argv[1]);
    if (normalizedURL2 == NULL) {
        fprintf(stderr, "failed to normalize\n");
        exit(1);  // Failed to normalize URL 
    }

    if (!isInternalURL(normalizedURL2)) {
        fprintf(stderr, "not an internal url\n");
        exit(1);
    }

    *seedURL = normalizedURL2;
    //free(normalizedURL2); 

    if (!pagedir_init(argv[2])) {
        fprintf(stderr, "page directory is invalid\n");
        exit(1);
    }
    *pageDirectory = argv[2];

    *maxDepth = atoi(argv[3]);
    if (*maxDepth < 0 || *maxDepth > 10) {
        fprintf(stderr, "maxDepth out of range, must be [0..10]\n");
        exit(1);
    }
}



/* initialize the hashtable and add the seedURL
initialize the bag and add a webpage representing the seedURL at depth 0
while bag is not empty
	pull a webpage from the bag
	fetch the HTML for that webpage
	if fetch was successful,
		save the webpage to pageDirectory
		if the webpage is not at maxDepth,
			pageScan that HTML
	delete that webpage
delete the hashtable
delete the bag
*/

void crawl(const char *seedURL, const char *pageDirectory, const int maxDepth) {
    // Initialize the hashtable and add the seedURL
    hashtable_t *visited = hashtable_new(1000);  
    hashtable_insert(visited, seedURL, "");

    // Initialize the bag and add a webpage representing the seedURL at depth 0
    bag_t *toCrawl = bag_new();
    webpage_t *seedPage = webpage_new((char *)seedURL, 0, NULL);
    bag_insert(toCrawl, seedPage);

    // While the bag is not empty
    webpage_t *currentPage;
    while ((currentPage = bag_extract(toCrawl)) != NULL) {
        // Fetch the HTML for that webpage
        //printf("here %s\n", webpage_getURL(currentPage));
        if (webpage_fetch(currentPage)) {
            // If fetch was successful
            printf("%d    Fetched: %s \n", webpage_getDepth(currentPage), webpage_getURL(currentPage));

            // Save the webpage to pageDirectory
            static int docID = 1;  // Start document IDs at 1
            pagedir_save(currentPage, pageDirectory, docID++);

            // If the webpage is not at maxDepth, pageScan the HTML
            if (webpage_getDepth(currentPage) < maxDepth) {
                pageScan(currentPage, toCrawl, visited);
            }


        } else {
            // Handle fetch failure if necessary
            fprintf(stderr, "Failed to fetch: %s\n", webpage_getURL(currentPage));
        }

        // Delete the current webpage after processing
        webpage_delete(currentPage);
    }
  

    // Cleanup: delete the hashtable and the bag
    hashtable_delete(visited, NULL);  // NULL here assumes no special delete function for URLs
    bag_delete(toCrawl, webpage_delete);  // Pass webpage_delete to free webpage data in the bag
}







// ./crawler seedURL pageDirectory maxDepth
int main(const int argc, char* argv[]){ //parse command line

  char* seedURL = NULL;
  char* pageDirectory = NULL;
  int maxDepth = -1;
  


  if (argc != 4 ) { //checks if number of inputs are correct 
        fprintf(stderr, "usage: ./crawler seedURL pageDirectory maxDepth\n");
        exit(1);
  }
 
  parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);
  crawl(seedURL, pageDirectory, maxDepth);


  return 0;

  
//numIndex

} 