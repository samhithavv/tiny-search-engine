//Samhitha Vallury, CS50FA24
//Github: samhithavv
//Lab 4 - TSE crawler.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "../libcs50/bag.h"
#include "../libcs50/mem.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/set.h"
#include "../libcs50/webpage.h"
#include "../common/pagedir.h"
#include "../libcs50/mem.h"


 static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);
 static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);

  
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

    // scan for urls
    while ((url = webpage_getNextURL(page, &pos)) != NULL) {
        //normalize
        char* normalizedURL = normalizeURL(url);

        printf("%d     Found: %s\n", webpage_getDepth(page), url);  //prints that url was found

        if (normalizedURL != NULL && isInternalURL(normalizedURL)) {
            // if the URL is internal and not seen before, insert it
            if (hashtable_insert(pagesSeen, normalizedURL, "")) {
                // create a new webpage object and insert
                webpage_t* newPage = webpage_new(normalizedURL, webpage_getDepth(page) + 1, NULL);
                printf("%d     Added: %s\n", webpage_getDepth(newPage), normalizedURL); //prints that it was added
                bag_insert(pagesToCrawl, newPage);
            } else {
                printf("%d    IgnDupl: %s\n", webpage_getDepth(page), normalizedURL);  //ignores the duplicate
                free(normalizedURL);
            }
        } else {
            printf("%d   IgnExtrn: %s\n", webpage_getDepth(page), url);  // prints tthat it is an external url
            free(normalizedURL);
        }

        // free the url
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
        exit(1);  //null check and exit
    }

    if (!isInternalURL(normalizedURL2)) {
        fprintf(stderr, "not an internal url\n"); //checks if it is an internal url
        exit(1);
    }

    *seedURL = normalizedURL2;

    if (!pagedir_init(argv[2])) { //checks for pagedirectory and exits
        fprintf(stderr, "page directory is invalid\n");
        exit(1);
    }

    *pageDirectory = argv[2]; //sets it to argv[2] if not exited

    *maxDepth = atoi(argv[3]); //makes the input into appropriate type

    if (*maxDepth < 0 || *maxDepth > 10) {
        fprintf(stderr, "maxDepth out of range, must be [0..10]\n"); //checks for maxDepth valid
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
    // initialize hashtable and inserts seedURL
    hashtable_t *visited = hashtable_new(1000);  
    hashtable_insert(visited, seedURL, "");

    // initialize the bag and add a webpage representing the seedURL at depth 0
    bag_t *toCrawl = bag_new();
    webpage_t *seedPage = webpage_new((char *)seedURL, 0, NULL);
    bag_insert(toCrawl, seedPage);

    // while the bag is not empty
    webpage_t *currentPage;
    while ((currentPage = bag_extract(toCrawl)) != NULL) {
        // fetch the html for the page
  
        if (webpage_fetch(currentPage)) {
            // prints if successfully fetched
            printf("%d    Fetched: %s \n", webpage_getDepth(currentPage), webpage_getURL(currentPage));

            // save the webpage to pageDirectory
            static int docID = 1;  // Start document IDs at 1
            pagedir_save(currentPage, pageDirectory, docID++);

            // if not at maxDepth, pageScan the HTML
            if (webpage_getDepth(currentPage) < maxDepth) {
                pageScan(currentPage, toCrawl, visited);
            }


        } else {
            // handle fetch issues if necessary
            fprintf(stderr, "Failed to fetch: %s\n", webpage_getURL(currentPage));
        }

        // delete webpage
        webpage_delete(currentPage);
    }

    // delete hashtable and bag
    hashtable_delete(visited, NULL);  
    bag_delete(toCrawl, webpage_delete);  
}





int main(const int argc, char* argv[]){ //parses command line

  char* seedURL = NULL;
  char* pageDirectory = NULL;
  int maxDepth = -1;

  if (argc != 4 ) { //checks if number of inputs are correct 
        fprintf(stderr, "usage: ./crawler seedURL pageDirectory maxDepth\n");
        exit(1);
  }
 
// calls parseArgs and crawl on inputs
  parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);
  crawl(seedURL, pageDirectory, maxDepth);

  return 0;

} 