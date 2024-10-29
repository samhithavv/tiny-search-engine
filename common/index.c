//Samhitha Vallury
//Github: samhithavv
//CS50 TSE - index module

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "hash.h"
#include "set.h"
#include "mem.h"
#include "counters.h"
#include <ctype.h>
#include <file.h>

//declarations of functions
typedef struct index index_t; 
index_t* index_new();
bool index_insert(index_t* index, const char* key, void* item);
void* index_find(index_t* index, const char* key);
void index_delete(index_t *index);
void index_save (index_t *index, const char* filename);

void counters_helper(void *arg, const int key, const int count);
void save_helper(void* arg, const char *key, void *item);
index_t* index_rebuild(const char *filename);


typedef struct index {
  hashtable_t *ht;         // making a hashtable
} index_t;


//build an inverted-index data structure mapping from words to
// (documentID, count) pairs, wherein each count represents the number of occurrences of the given word in the given document. 
//Ignore words with fewer than three characters, and "normalize" the word before indexing. (Here, "normalize" means to convert all letters to lower-case.)

index_t* index_new(){
   index_t* index = mem_malloc(sizeof(index_t)); //malloc memory
    //if mem allocation fails
    if (index == NULL){
        return NULL;
    }
    index->ht = hashtable_new(700); //random from 200 to 900, as in instructions 

    return index;
}


bool index_insert(index_t* index, const char* key, void* item) {
   if (index == NULL || key == NULL || item == NULL){ //null check
        return false; 
    }
    if (hashtable_insert(index->ht, key, item)){ //insert into hastable given key and item
       return true;
    }
    return false; //if not inserted

}



void* index_find(index_t* index, const char* key){
    
    if (index == NULL || key == NULL){ //null check
        return NULL;
    }
    return(hashtable_find(index->ht, key)); //returns whatever hashtable find gives

}


//index find all for later -- finds how many occurrences for a word across all documents, might not need it now

void index_delete(index_t *index){

    if (index== NULL){
        return; //null check
    }

    hashtable_delete(index->ht,  (void (*)(void *))counters_delete); //calls delete on hashtable
    mem_free(index); //frees memorry

}



//one line per word, one word per line
// each line provides the word and one or more (docID, count) pairs, in the format
// word docID count [docID count]...
// where word is a string of lower-case letters,
// where docID is a positive non-zero integer,
// where count is a positive non-zero integer,
// where the word and integers are separated by spaces;
// note the [ ] brackets and elipses ... are not part of the file format – we use them here to indicate the docID count occurs one or more times.

void index_save (index_t *index, const char* filename){
    if (index == NULL || filename == NULL) {
        return; //null check
    }

    FILE *file = fopen(filename, "w"); //checks if can be written to
    if (file == NULL) {
        fprintf(stderr, "In index_save - Error: could not open file %s for writing.\n", filename); 
        return;
    }


    hashtable_iterate(index->ht, file, save_helper); //iterates and prints through the hashtable

    fclose(file);
}


void counters_helper(void *arg, const int key, const int count) { //to help print with counters
    if (arg == NULL) {
        return;
    }

    FILE *fp = (FILE *) arg; //cast file
    fprintf(fp, " %d %d", key, count); //prints key and count of counter
}


void save_helper(void *arg, const char *key, void *item) { //helps print
    FILE *fp = (FILE *)arg;   // cast file
    counters_t *ctrs = (counters_t *)item;

    if (fp == NULL) { //null check
        fprintf(stderr, "Error: file pointer is NULL in save_helper.\n");
        return;  
    }

    fprintf(fp, "%s", key); //print hashtable key

    // call counters helper to print the value of the slot
    counters_iterate(ctrs, fp, counters_helper);

    //add a new line for readability
    fprintf(fp, "\n");
}





//write the index file into a text file
//repopulate the 
//loop through using file.next word
//read to understand file.h to understand fileread method

index_t* index_rebuild(const char *filename) {
    // try to open file
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return NULL;
    }

    //make new index
    index_t *index = index_new();
    if (index == NULL) {
        fclose(fp);
        return NULL; //null check
    }

    char *word;        // holds the word
    int docID, count;  // document ID and word count

    // read each word using file.h methods
    while ((word = file_readWord(fp)) != NULL) {
        if (strlen(word) == 0) {  //checks for empty strings
            free(word);
            continue;
        }

        // find the previous counter
        counters_t *ctrs = index_find(index, word);
        if (ctrs == NULL) {
            // make a new counter if it doens't exist already
            ctrs = counters_new();
            if (ctrs == NULL) {
                free(word); //free if null
                fclose(fp);
                index_delete(index); //delete for memory purposes
                return NULL;
            }
            index_insert(index, word, ctrs); //insert into index otherwise
        }

       
       while (fscanf(fp, "%d %d", &docID, &count) == 2) { //checks if it is two
            counters_set(ctrs, docID, count); //adds to the counters
        }
       

        free(word); //memory freeing
    }

    //close file and return new index
    fclose(fp);
    return index;
}

