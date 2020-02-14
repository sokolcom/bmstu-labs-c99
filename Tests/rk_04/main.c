#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "define.h"
#include "processing.h"



int main(int32_t argc, char **argv)
{

    char *filename = argv[1];

    /* The algorithm is veeeeery simple
     * Source file: "To be or not to be"
     * List: be -> to -> not -> or -> be -> To -> NULL fill in just like stack)
     * Reverse each word: eb -> ot -> ton -> ro -> eb -> oT -> NULL 
     * Done! 
     * So why not??? :)
     */

    reverse(filename);

    return SUCCESS;
}

