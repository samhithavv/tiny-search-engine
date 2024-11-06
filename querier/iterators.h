//Samhitha Vallury
//github: samhithavv
//TSE querier - iterators for querier

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


// creates a duplicate of the original counters object
counters_t* counters_duplicate(counters_t *original);

// helper function that copies each (key, count) pair from original to duplicate
void counters_copy_helper(void *arg, const int key, const int count);

// merges two counters objects by adding the counts for matching keys
void counters_union(counters_t *result, counters_t *temp);

// helper function that merges counts during counters unionization
void union_helper(void *result, const int key, const int count);

// makes the intersection of two counters and stores the min count for each key in result
counters_t* counters_intersect(counters_t *c1, counters_t *c2);

// helper function to add the min count for each applicable key during intersection
void intersect_helper(void *arg, const int key, const int count);




