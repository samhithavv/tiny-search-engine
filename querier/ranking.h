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


// helper function to find the max score document in counters
void findMaxHelper(void *arg, const int key, const int count);

// function that finds the max scoring document in counters and resets its score
int findMaxScoreDoc(counters_t *counters, int *maxScore);

// prints the ranked search results based on  scores
void printRankedResults(counters_t *counters, index_t *index, const char* pageDir);

// hllper function that counts documents with non-zero scores in counters
void countDocsHelper(void *arg, const int key, const int count);




