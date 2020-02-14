#include <stdio.h>

#include "define.h"
#include "data_struct.h"
#include "file_parsing.h"



int main(int argc, char **argv)
{
    char *filename = argv[1];
    int amount;

    text_t src_text = parse_file(filename, &amount);
    print_data(FILE_OUT, src_text, amount);

    look_alike(src_text, amount);  // find similar sentences
    
    // free_text(src_text);  // OS is smart enough to free data by itself

    printf("Data proceeded successfully!");
    return SUCCESS;

}

