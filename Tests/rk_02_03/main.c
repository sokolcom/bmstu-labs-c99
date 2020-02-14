/*
TEST:

For in.txt result:

2120
1220
2230
2221
*/

#include <stdio.h>

#define SUCCESS 0
#define FAILURE 1



int calculate_dimension(FILE* source)
{
    int dimension = 0;

    int row;
    while (fscanf(source, "%d", &row) == 1)
        dimension++;

    rewind(source);
    return dimension;
}


int decode_element(const char symbol)
{
    int element = 0;
    char symbols[] = "01";

    while (symbols[element] != symbol)
        element++;
    // DEBUG printf("DECODED: %d; SYMBOL WAS %c\n", element, symbol);
    return element;
}


int get_element(FILE* source, const int row, const int col)
{
    rewind(source);

    int scanned_row;
    for (int i = 0; i < row; i++)
        fscanf(source, "%d", &scanned_row);

    char symbol;
    if (row > 0)
        fscanf(source, "%c", &symbol);

    for (int j = 0; j <= col; j++)
        fscanf(source, "%c", &symbol); 
    
    // DEBUG if (symbol == '\n')
    // DEBUG    printf("FIASCO!\n");
    return decode_element(symbol);
}


int calculate_element(FILE* source, const int row, const int col, const int dime)
{
    int element = 0;

    for (int i = 0; i < dime; i++)
    {
        int multiplier_1 = get_element(source, row, i);
        int multiplier_2 = get_element(source, i, col);
        // DEBUG printf("MULTIPLIERS: %d and %d\n", multiplier_1, multiplier_2); 
        element += multiplier_1 * multiplier_2;
    }
    // DEBUG printf("ELEMENT: %d\n", element);
    return element;
}


void power_matrix(FILE* source, FILE* output)
{
    int n = calculate_dimension(source);
    // DEBUG printf("DIMENSION: %d\n", n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int element = calculate_element(source, i, j, n);
            fprintf(output, "%d", element);
        }
        fprintf(output, "\n");
    }
}


int main()
{
    FILE* input_file = fopen("in.txt", "r");
    if (input_file)
    {
        FILE* output_file = fopen("out.txt", "w");
        
        power_matrix(input_file, output_file);

        fclose(output_file);
        fclose(input_file);
        return SUCCESS;
    }
    else
    {
        printf("File doesn't exist!\n");
        return FAILURE;
    }
}

