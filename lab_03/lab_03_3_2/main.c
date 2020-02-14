// Задание 2, вараинт 3
// Проверить выполняется ли правило "трех сигм" для введеных чисел

#include <stdio.h>
#include <math.h>

#define ZERO 0
#define ONE 1
#define POWER_TWO 2
#define THREE 3

#define YES 1
#define NO 0
#define ONE_NUM 1
#define WRONG_DATA -1
#define RULE_FAIL 0
#define RULE_OK 1

#define SUCCESS 0
#define FAILURE 1
#define NO_NAME_ERROR -1
#define EXIST_ERROR -2
#define EMPTY_ERROR -3
#define VALUE_ERROR -4



int calculate_mean(FILE* source, double *mean)
{
    double sum = ZERO;
    double element;
    int amount = ZERO;
    
    int check = fscanf(source, "%lf", &element);
    while (check == ONE_NUM)
    {
        sum += element;
        amount++;
        check = fscanf(source, "%lf", &element);
    }
    if (!check)
        return WRONG_DATA;

    if (amount)
        *mean = sum / amount;    
    return amount;
}


double calculate_variance(FILE* source, const double mean, const int amount)
{
    double quadratic_sum = ZERO;
    double element;

    while (fscanf(source, "%lf", &element) == ONE_NUM)
        quadratic_sum += pow(element - mean, POWER_TWO);

    return quadratic_sum / amount;
}


int check_distribution_rule(FILE* source, const double mean, const double deviation)
{
    double element;

    while (fscanf(source, "%lf", &element) == ONE_NUM)
        if (element < mean - THREE * deviation || 
            element > mean + THREE * deviation)
            return RULE_FAIL;
    return RULE_OK;
}

int three_sigma_rule(FILE* source)
{
    double mean;
    int amount = calculate_mean(source, &mean);
    if (amount > ZERO)
    {
        rewind(source);
        double variance = calculate_variance(source, mean, amount);
        double deviation = sqrt(variance);

        rewind(source);
        if (check_distribution_rule(source, mean, deviation))
            printf("%d", YES);
        else
            printf("%d", NO);
    }
    else if (amount == ZERO)
    {
        printf("File is empty!\n");
        return EMPTY_ERROR;
    }
    else if (amount == WRONG_DATA)
    {
        printf("File consists invalid data!\n");
        return VALUE_ERROR;
    }
    return RULE_OK;
}



int main(int argc, char **argv)
{
    if (argc == ONE)
    {
        printf("No files entered!\n");
        return NO_NAME_ERROR;
    }

    FILE* input_file = fopen(argv[ONE], "r");
    if (input_file)
    {
        if (three_sigma_rule(input_file) > ZERO)
        {
            fclose(input_file);
            return SUCCESS;
        }
        else
        {
            fclose(input_file);
            return FAILURE;
        }
    }
    else
    {
        printf("No file with the entered name found!\n");
        return EXIST_ERROR;
    }
}

