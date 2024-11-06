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

//counters_duplicate
//counters_unionize
//counters_intersect


//declarations
counters_t* counters_duplicate(counters_t *original);
void counters_copy_helper(void *arg, const int key, const int count);
void counters_union(counters_t *result, counters_t *temp);
void union_helper(void *result, const int key, const int count);
counters_t* counters_intersect(counters_t *c1, counters_t *c2);
void intersect_helper(void *arg, const int key, const int count);


// holds both result and second counters object to pass to intersect_helper
typedef struct intersect_args {
    counters_t *result;
    counters_t *c2;
} intersect_args_t;

counters_t* counters_intersect(counters_t *c1, counters_t *c2) {
    if (c1 == NULL || c2 == NULL) return NULL;

    // holds new counters result
    counters_t *result = counters_new();
    if (result == NULL) {
        return NULL;  // null check
    }
        
    intersect_args_t args = { .result = result, .c2 = c2 };  //had help from TA


    //iterates through the counter using args
    counters_iterate(c1, &args, intersect_helper);

    return result;
}

// helps finds the keys that intersect
void intersect_helper(void *arg, const int key, const int count) {
    intersect_args_t *args = (intersect_args_t *)arg; //casts as object
    counters_t *result = args->result; //sets the result counter to the struct's result
    counters_t *c2 = args->c2; // sets the second counter to struct's second counter

    // gets the count for that counter
    int c2_count = counters_get(c2, key);

    if (c2_count > 0) {
        // if key is in both, then get both
        int min_count = (count < c2_count) ? count : c2_count;
        counters_set(result, key, min_count);
    }
}




// adds counts for keys that match
void counters_union(counters_t *result, counters_t *temp) {
    if (result == NULL || temp == NULL) return;

    // goes through all entries with the helper
    counters_iterate(temp, result, union_helper);
}

// helps to merge counts
void union_helper(void *result, const int key, const int count) {
    counters_t *result_counters = (counters_t *)result; //makes new counters object

    int existing_count = counters_get(result_counters, key);
    int new_count = existing_count + count; //if found, update the value with new value

    // sets the count to whatever is found
    counters_set(result_counters, key, new_count);
}



// helper function to copy each pair from original to duplicate
void counters_copy_helper(void *arg, const int key, const int count) {
    counters_t *duplicate = (counters_t *)arg;
    counters_set(duplicate, key, count);
}

counters_t* counters_duplicate(counters_t *original) {
    if (original == NULL) return NULL;

    // creates a new counters structure for the duplicate
    counters_t *duplicate = counters_new();
    if (duplicate == NULL) {
        return NULL;  //null check
    }

    // goes through the original counters object, and copys each item to the duplicate
    counters_iterate(original, duplicate, counters_copy_helper);

    return duplicate; //returns the duplicate
}


