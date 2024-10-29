//Samhitha Vallury
//github: samhithavv
//TSE indexer - indexer.c


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
#include "../common/index.h"
#include "../libcs50/mem.h"
#include "../libcs50/counters.h"
#include "../common/word.h"


//declarations
void indexBuild(const char* pageDir, const char* indexFilename);
void indexPage(index_t *index, webpage_t *webpage, const int docID);



void indexBuild(const char* pageDir, const char* indexFilename){
    index_t* index = index_new(); //makes new index
    if (index == NULL) { //null check
        fprintf(stderr, "Error: could not create index\n");
        return;
    }

    int docID = 1; //sets to one
 
    if (pageDir == NULL) { //null check
        fprintf(stderr, "Error: pageDir is NULL in indexBuild\n");
        return;
    }
    bool check = true; //setting up while loop
    while (check) {
        // try to load the webpage from the file
        webpage_t* webpage = load_webpage(pageDir, docID); 
        webpage_fetch(webpage);  

        if (webpage == NULL) {
            // if webpage can't be loaded, break  loop
            check = false;
            break;
        }
        // pass webpage and docID to indexPage to process webpage and build index
        indexPage(index, webpage, docID);

        // delete webpage
        webpage_delete(webpage);
        // increment for next
        docID++;
    }


    if (index != NULL) { //makes sure it's not null before saving 
        index_save(index, indexFilename);
        index_delete(index);
        
    } else {
        fprintf(stderr, "Error: Index is null in indexBuild.\n");
    } //used to check
    


}






//indexPage
//  steps through each word of the webpage,
//    skips trivial words (less than length 3),
//    normalizes the word (converts to lower case),
//    looks up the word in the index,
//      adding the word to the index if needed
//    increments the count of occurrences of this word in this docID
void indexPage(index_t *index, webpage_t *webpage, const int docID) {
    if (index == NULL || webpage == NULL) {
        return; // ensures the index and webpage are valid
    }

    int pos = 0; // starting position
    char *word;

    // get words from the webpage until none are left
    while ((word = webpage_getNextWord(webpage, &pos)) != NULL) {
        // make lowecase
        normalize_word(word);

        // no less than 3 chars word
        if (strlen(word) >= 3) {
            // gets counters
            counters_t *ctrs = index_find(index, word);

            // if no counters exist, make new counters object
            if (ctrs == NULL) {
                ctrs = counters_new();
                if (ctrs == NULL) {
                    free(word); // free memory if allocation fails
                    continue; // move to next
                }

                // insert the new counters into the index
                if (!index_insert(index, word, ctrs)) {
                    counters_delete(ctrs); //free memory
                    free(word); // free memroy
                    continue; // move to next word
                }
            }

            // increments the count for docID in counters
            int current_count = counters_get(ctrs, docID);
            counters_set(ctrs, docID, current_count + 1);
        }

        free(word);
    }
}


//main
//parse the command line, validate parameters, initialize other modules
//call indexBuild, with pageDirectory


int main(int argc, char *argv[]) {
   
    if (argc != 3) { //usage check
        fprintf(stderr, "usage: ./indexer pageDirectory indexFilename\n");
        exit(1);

    }
    
    const char *pageDirectory = argv[1]; //sets to appropriate values
    const char *indexFilename = argv[2];

     if (!pagedir_validate(pageDirectory)) { //validates directory
        fprintf(stderr, "Error: %s is not a valid crawler-produced directory.\n", pageDirectory);
        exit(1);
    }


    FILE *indexFile = fopen(indexFilename, "w");  //opens for writing
    if (indexFile == NULL) {
        fprintf(stderr, "Error: could not open file %s for writing.\n", indexFilename);
    
        exit(1);
    }


    index_t *index = index_new(); //makes new index
    if (index == NULL) {
        fprintf(stderr, "Error: could not initialize index.\n");
        exit(1);
    }


    // builds the index from the pageDirectory content

    indexBuild(pageDirectory, indexFilename);
    
    //close and delete
    fclose(indexFile); 
    index_delete(index);

    return 0;

}   
