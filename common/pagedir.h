#ifndef __PAGEDIR_H
#define __PAGEDIR_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../libcs50/webpage.h"


/*
   Initializes a directory for the crawler to use by creating a special file .crawler within the specified pageDirectory. 
    Constructs the path for the .crawler file, opens files for writing, and if successful, closes the file and returns true. 
    If there's an error (such as memory allocation failure or inability to open the file), it returns false.
*/

bool pagedir_init(const char* pageDirectory);



/*
Saves the content of a fetched webpage into a file inside the specified pageDirectory. 
The file is named based on the provided docID. 
It writes the URL, depth, and HTML content of the webpage into the file. 
If there's an error opening the file for writing, it prints an error message and terminates the function without saving the page.

*/

void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);


#endif