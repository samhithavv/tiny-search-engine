//Samhitha Vallury
//github: samhithavv
//TSE querier - rankings.c


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



//function declarations
void findMaxHelper(void *arg, const int key, const int count);
int findMaxScoreDoc(counters_t *counters, int *maxScore);
void printRankedResults(counters_t *counters, index_t *index, const char* pageDir);
void countDocsHelper(void *arg, const int key, const int count);
const char* getURL(int docID);


// helper function to find the document with the highest score
typedef struct {
    int maxDocID;
    int maxScore;
} maxResult_t; //make new struct to store the docID and the maxScore

void findMaxHelper(void *arg, const int key, const int count) {
    maxResult_t *result = (maxResult_t *)arg; //casts the argument to a maxResult object
    if (count > result->maxScore) {
        result->maxDocID = key; //sets maxDocID to key
        result->maxScore = count; //sets maxScore to count
    }
}

// function to find the highest scoring document in counters
int findMaxScoreDoc(counters_t *counters, int *maxScore) {
    maxResult_t result = { .maxDocID = -1, .maxScore = 0 };
    counters_iterate(counters, &result, findMaxHelper); //iterates throguh counters with helper function
    *maxScore = result.maxScore;
    if (result.maxDocID != -1) {
        counters_set(counters, result.maxDocID, 0); // reset the count
    }
    return result.maxDocID;
}

// function that prints the ranked results in necessary format
void printRankedResults(counters_t *counters, index_t *index, const char* pageDir) {
    int maxScore, docID, docCount = 0;

    // determines the number of files to be ranked
    counters_iterate(counters, &docCount, countDocsHelper); // counts the number of docs with non-zero scores
    printf("Matches %d documents (ranked):\n", docCount); //print statement

    // follows method provided in instructions to print in decreasing order
    while ((docID = findMaxScoreDoc(counters, &maxScore)) != -1 && maxScore > 0) {
        webpage_t* webpage = load_webpage(pageDir, docID); 
       
        const char* url = webpage_getURL(webpage);
        if (url != NULL) {
            printf("score\t%d doc\t%d: %s\n", maxScore, docID, url);
        }
        counters_set(counters, docID, 0);  // resets so that it doesn't print it out again
       
        webpage_delete(webpage); //deletes the webpage
    }
}


void countDocsHelper(void *arg, const int key, const int count) { //helps count the docs
    int *docCount = (int *)arg;
    if (count > 0) {
        (*docCount)++; //increments if count is greater than 0
    }
}
