//Samhitha Vallury, CS50FA24
//Github: samhithavv
//Lab 4 - Word module


//normalizes the word into lowercase

#include <ctype.h>
#include <stddef.h> 

void normalize_word(char* word) {
    if (word == NULL) { // null check and return
         return;
    }

    for (int i = 0; word[i]; i++) { //makes it lowercase for every character
        word[i] = tolower((unsigned char)word[i]); 
    }
}

