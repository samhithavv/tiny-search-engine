//Samhitha Vallury
//github: samhithavv
//TSE indexer - indextest.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../common/index.h"   // include path for index functions
#include "../libcs50/file.h"   // include path for file comparison


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: ./indextest old_index_file new_index_file\n");
        exit(1);
    }

    const char *old_file = argv[1];
    const char *new_file = argv[2];

    // Rebuild index from the old file
    index_t *index = index_rebuild(old_file);
    if (index == NULL) {
        fprintf(stderr, "Error: Failed to rebuild index from %s\n", old_file);
        exit(1);
    }

    // Save the rebuilt index to the new file
    index_save(index, new_file);
    index_delete(index);

   
}
