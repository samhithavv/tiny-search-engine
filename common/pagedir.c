//Samhitha Vallury, CS50FA24
//Github: samhithavv
//Lab 4 - Pagedir for 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../libcs50/webpage.h"
#include "../libcs50/bag.h"
#include "../libcs50/mem.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/set.h"
#include "../libcs50/bag.h"
#include <assert.h>

/* construct the pathname for the .crawler file in that directory
open the file for writing; on error, return false.
close the file and return true.
*/
bool pagedir_init(const char* pageDirectory)
{
    const char *crawlerFileName = "/.crawler"; //create the file name

    // allocates memory for the full path of the .crawler file
    char *crawlerFilePath = malloc(strlen(pageDirectory) + strlen(crawlerFileName) + 1); //accounts for null terminator
    if (crawlerFilePath == NULL) { 
        fprintf(stderr, "Out of memory!!"); //memory check
        return false;
    }

    //makes the full file path
    strcpy(crawlerFilePath, pageDirectory);
    strcat(crawlerFilePath, crawlerFileName);

    // opens the file writing
    FILE *file = fopen(crawlerFilePath, "w");
    if (file == NULL) {
        free(crawlerFilePath);  // frees the memory for the file path
        return false;
    }

    // closes the file
    fclose(file);

    free(crawlerFilePath); //free if successful
    return true;

}

/* construct the pathname for the page file in pageDirectory
open that file for writing
print the URL
print the depth
print the contents of the webpage
close the file*/

void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID){

    char filepath[256];  // arbitrary size
    snprintf(filepath, sizeof(filepath), "%s/%d", pageDirectory, docID); 

    //opens the file to write in it
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to create file %s\n", filepath);
        return;
    }

    //prints the url of the page to the file
    fprintf(file, "%s\n", webpage_getURL(page));

    //prints the depth of the page to the file
    fprintf(file, "%d\n", webpage_getDepth(page));

    //prints the contents of the page to the file
    fprintf(file, "%s\n", webpage_getHTML(page));

    // close file
    fclose(file);

}