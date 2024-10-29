//Samhitha Vallury, CS50FA24
//Github: samhithavv
//Lab 4 - Pagedir module

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
#include "../libcs50/file.h"
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


// takes file from crawler output and gets the url inside of it
webpage_t* load_webpage(const char* pageDir, const int docID) {

    char* filename = malloc(strlen(pageDir) + 10); //malloc memory for filename
    
    sprintf(filename, "%s/%d", pageDir, docID); //make the filename


    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        free(filename); //frees
        return NULL;
    }
    
    //reads the lines for depth, url, and html
    char* url = file_readLine(fp);
    char* depth = file_readLine(fp);
    char* html = file_readFile(fp);

    //makes new webpage object based on that
    webpage_t* webpage = webpage_new(url, atoi(depth), html);
    fclose(fp);
    free(filename); //frees the filenmae
    free(depth);

    return webpage; //return new webpage object
    
}



bool pagedir_validate(const char *pageDirectory) {
    if (pageDirectory == NULL) { //null check
        fprintf(stderr, "Error: pageDirectory is NULL\n");
        return false;
    }

    // make the path to the .crawler file
    char crawler_path[strlen(pageDirectory) + strlen("/.crawler") + 1];

    sprintf(crawler_path, "%s/.crawler", pageDirectory);

    // checking by opening the .crawler file to see if it exists
    FILE *file = fopen(crawler_path, "r");
    if (file) {
        fclose(file);  //if file exists, return true
        return true;
    } else {
        return false;
    }
}

