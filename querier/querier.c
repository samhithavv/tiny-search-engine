//Samhitha Vallury
//github: samhithavv
//TSE querier - querier.c

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
#include "ranking.h"
#include "iterators.h"


#define MAX_QUERY_LENGTH 1000
#define MAX_TOKENS 256
#define MAX_WORD_SIZE 256



/* main 
parseargs - 
    check if page dir is valid
    check if index is valid
querier evaluations


use iterators for union and intersection
ranking

arg, key, count for union, intersection, ranking

hashtable of counters
*/

//declarations
void checkQueries(index_t* index, const char* pageDir);
void normalize(char *str);
char **tokenizeQuery(char *query);
bool validateQuerySyntax(char **tokens);
void freeTokens(char **tokens);
void printCleanQuery(char **tokens);
counters_t *processQuery(char **tokens, index_t *index);



int main(int argc, char *argv[]) { 
     if (argc != 3) { //usage check
        fprintf(stderr, "usage: ./querier pageDirectory indexFilename\n");
        exit(1);

    }

    const char *pageDir = argv[1]; //sets to appropriate values
    const char *indexFilename = argv[2]; 

    if (!pagedir_validate(pageDir)) { //validates directory
        fprintf(stderr, "Error: %s is not a valid crawler-produced directory.\n", pageDir);
        exit(2);
    }

    FILE *indexFile = fopen(indexFilename, "r");  //opens for writing
   
    if (indexFile == NULL) {
        fprintf(stderr, "Error: could not open file %s for reading.\n", indexFilename);
        exit(3);
    }

    
    index_t* index = index_rebuild(indexFilename); //makes the index object

    checkQueries(index, pageDir); // validates the query

    index_delete(index); //frees memory

    fclose(indexFile);
    return 0;
    
}


void checkQueries(index_t* index, const char* pageDir) {
    char query[MAX_QUERY_LENGTH];   // holds the query
    
    bool check = true;

    while (check){ //loop until broken
        printf("Query? "); 

        if (fgets(query, sizeof(query), stdin) == NULL){
            break; //ends if null input
        }
        // normalizes to lowercase
        normalize_word(query);

        bool check2 = true;

        // check that only letters and spaces exist in query
        for (int i = 0; query[i] != '\0'; i++) {
            if (!isalpha(query[i]) && !isspace(query[i])) {
                printf("Error: bad character '%c' in query.\n", query[i]);
                check2 = false;
            }
        }
        if (check2 == false){
            printf("-----------------------------------------------\n"); //prints ending in case it reaches here
            continue;
        }
    

        // tokenize the query
        char **tokens = tokenizeQuery(query);
        if (tokens == NULL) {
            printf("-----------------------------------------------\n"); //prints ending in case it reaches here
            printf("Error: Tokenization failed.\n");
            continue;
        }

        // validates query syntax
        if (!validateQuerySyntax(tokens)) {
            freeTokens(tokens);
            printf("-----------------------------------------------\n"); //prints ending in case it reaches here
            continue;
        }

        // prints clean
        printCleanQuery(tokens);

        
        counters_t* result = processQuery(tokens, index); //processes the query

        if (result != NULL) {
            printRankedResults(result, index, pageDir); // uses the ranking functions from rankings.c
            counters_delete(result);
        } else {
            printf("No matches found.\n");
            
        }

        printf("-----------------------------------------------\n");
        // frees the tokens array
        freeTokens(tokens);
        
    }
    

  
}

char **tokenizeQuery(char *query) { //to tokenize
    char **tokens = malloc(MAX_TOKENS * sizeof(char*)); //memory for the query
    int tokenCount = 0;

    char word[MAX_WORD_SIZE];
    int wordIndex = 0; //index is 0

    for (int i = 0; query[i] != '\0'; i++) {
        if (!isspace(query[i])) { //checks to make sure it's not a space
            // makes
            word[wordIndex++] = query[i];
        } else if (wordIndex > 0) {
            // word ends, null terminate, store the word, and reset
            word[wordIndex] = '\0';
            tokens[tokenCount] = malloc(wordIndex + 1);
            strcpy(tokens[tokenCount], word);
            tokenCount++;
            wordIndex = 0;
        }
    }

    // extra check to add the last word if it exists
    if (wordIndex > 0) {
        word[wordIndex] = '\0';
        tokens[tokenCount] = malloc(wordIndex + 1);
        strcpy(tokens[tokenCount], word);
        tokenCount++;
    }

    tokens[tokenCount] = NULL;  // empties the tokens array
    return tokens;
}


bool validateQuerySyntax(char **tokens) {
    if (tokens[0] == NULL) {
        return true;  // null check
    }
    const char *andOperator = "and"; //made variables
    const char *orOperator = "or";

    // find the last index
    int lastIndex = 0;
    while (tokens[lastIndex] != NULL) lastIndex++; //gets the last index
    lastIndex--;  // 

    // checks for and in the first
    if (strcmp(tokens[0], andOperator) == 0) {
        printf("Error: Query cannot start with 'and'.\n");
        return false;
    }
    //checks if first word is or
    if (strcmp(tokens[0], orOperator) == 0) {
        printf("Error: Query cannot start with 'or'.\n");
        return false;
    }

    //check if ends with and
    if (strcmp(tokens[lastIndex], andOperator) == 0) {
        printf("Error: Query cannot end with 'and'.\n");
        return false;
    }
    //check if ends with or
    if (strcmp(tokens[lastIndex], orOperator) == 0) {
        printf("Error: Query cannot end with 'or'.\n");
        return false;
    }

    for (int i = 0; tokens[i + 1] != NULL; i++) {
        //checks for and - or consecutive sequence
        if (strcmp(tokens[i], andOperator) == 0 && strcmp(tokens[i + 1], orOperator) == 0) {
            printf("Error: 'and' and 'or' cannot be adjacent\n"); 
            return false;
        }
        //checks for or - and consecutive sequence
        if (strcmp(tokens[i], orOperator) == 0 && strcmp(tokens[i + 1], andOperator) == 0) {
            printf("Error: 'or' and 'and' cannot be adjacent\n"); 
            return false;
        }
        //checks for and - and consecutive sequence
         if (strcmp(tokens[i], andOperator) == 0 && strcmp(tokens[i + 1], andOperator) == 0) {
            printf("Error: 'and' and 'and' cannot be adjacent\n"); 
            return false;
        }
        //checks for or - or consecutive sequence
        if (strcmp(tokens[i], orOperator) == 0 && strcmp(tokens[i + 1], orOperator) == 0) {
            printf("Error: 'or' and 'or' cannot be adjacent\n"); 
            return false;
        }
    }

    return true;  //returns true if passes tests
}





void printCleanQuery(char **tokens) {
    printf("Query: ");
    for (int i = 0; tokens[i] != NULL; i++) {
        printf("%s", tokens[i]);
        if (tokens[i + 1] != NULL) {
            printf(" ");
        }
    }
    printf("\n"); //prints the query with spaces in between each word
}


void freeTokens(char **tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]); //frees the tokens
    }
    free(tokens);
}




counters_t *processQuery(char **tokens, index_t *index) {
    counters_t *result = NULL;
    counters_t *temp = NULL; //make temp null
    
    for (int i = 0; tokens[i] != NULL; i++) {

        // if it finds a regular word for searching
        if (strcmp(tokens[i], "and") != 0 && strcmp(tokens[i], "or") != 0) {
        
            counters_t *wordCounters = index_find(index, tokens[i]); //find the counters for the object
            
            if (wordCounters != NULL) {
                if (temp == NULL) {
                    // set temp to the duplicate to avoid modifying the original
                    temp = counters_duplicate(wordCounters);
                } else {
                    // intersect with temp and wordCounters
                    counters_t *new_temp = counters_intersect(temp, wordCounters);
                    counters_delete(temp); // free temp once intersected
                    temp = new_temp; //set temp to the new result of counters

                    // check if temp is null
                    if (temp == NULL) {
                        // break if null - helps to prevent the counters object from intersecting if one is null
                        break;
                    }
                }
            } else {
                // if no results, delete temp
                  counters_delete(temp);
                  temp = NULL;
                  break;
            }



        } else if (strcmp(tokens[i], "or") == 0) {
            // unionize and set temp to result
            if (result == NULL) {
                result = temp;
            } else {
                counters_union(result, temp); //unionize into result
                counters_delete(temp); //free temp
            }
            temp = NULL;
        } else if (strcmp(tokens[i], "and") == 0) {
            // continues if it finds and
            continue;
        }
    }

    // unionizes result with temp
    if (temp != NULL) {
        if (result == NULL) {
            result = temp;
        } else {
            counters_union(result, temp); //union
            counters_delete(temp); //deletes
        }
    }
    
    return result;
}


