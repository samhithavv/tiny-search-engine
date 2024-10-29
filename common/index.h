//Samhitha Vallury
//Github: samhithavv
//CS50 TSE - index.h module

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdbool.h>


typedef struct index index_t; 



// index_new()
// Creates and returns a new, empty index structure.
// has a hashtable that maps each unique word (key) to a counters object (item)
index_t* index_new();

// Inserts a new key-item pair into the index. 
// Returns: true if successful, false otherwise (e.g., if index or key is NULL).
bool index_insert(index_t* index, const char* key, void* item);

// Finds the item associated with a given key in the index
// Returns the item if found, or NULL otherwise
void* index_find(index_t* index, const char* key);

// Deletes the index and frees all  memory
void index_delete(index_t *index);

// Saves the index to a file in a specific format
// One word per line with (docID, count) pairs
void index_save (index_t *index, const char* filename);

//Helps with printing values, which are counters, of hashtable
 void counters_helper(void *arg, const char *key, void *item);

//Helps with printing keys of hashtable
 void save_helper(void* arg, const char *key, void *item);

// Returns the rebuilt index or NULL if errors occur
index_t* index_rebuild(const char *filename);



#endif