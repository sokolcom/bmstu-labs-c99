#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#include "../include/define.h"
#include "../include/struct.h"
#include "../include/list_interface.h"
#include "../include/arithmetics.h"



// Factorize entered number
int32_t factorize_number(node_t **const head, int32_t number)
{
    int32_t multiplier = 2;
    int32_t power = 0;

    while (number > MIN_VALUE)
    {
        while ((number % multiplier == 0))
        {
            number /= multiplier;
            power++;
        }
#ifdef __DEBUG__
        printf("PRIME^POWER: %" PRId32 "^%" PRId32"\n", multiplier, power);
        printf("CURRENT VALUE: %" PRId32 "\n\n", number);
#endif
    // If another prime multiplier consists in number
        if (power)
        {
            if (!push_node(head, multiplier, power))
            {
                power = 0;
            }
            else
            {   
                return ALLOC_NODE_ERROR;
            }       
        }

        // That's correct, `cause if we've finished with, for example, 2
        // then we've done with 4,8,16,... etc 
        // (No need to implement Sieve of Eratosthenes algorithm)
        multiplier++;
    }

    return SUCCESS;
}


// Multiply two factorized numbers
int32_t multiply_factorized(const node_t *head_1, const node_t *head_2, node_t **const head_result)
{   
    node_t *temp_result = NULL;  // The result will be reversed here
    int32_t sum_power;

    // While we don't pass through each number
    while (head_1 || head_2)
    {
        // If first number is already over 
        if (!head_1)
        {
            if (!push_node(&temp_result, head_2->base, head_2->power))
            {
                head_2 = head_2->next;
            }
            else
            {   
                free_list(temp_result);
                return ALLOC_NODE_ERROR;
            }
        }
        // If second number is already over
        else if (!head_2)
        {
            if (!push_node(&temp_result, head_1->base, head_1->power))
            {
                head_1 = head_1->next;
            }
            else
            {
                free_list(temp_result);
                return ALLOC_NODE_ERROR;
            }
        }
        // Trivial case (still have prime multipliers in both numbers)
        else
        {
            // First number's multiplier is bigger than second one's
            if ((head_1->base) > (head_2->base))
            {
                if (!push_node(&temp_result, head_1->base, head_1->power))
                {
                    head_1 = head_1->next;
                }
                else
                {
                    free_list(temp_result);
                    return ALLOC_NODE_ERROR;
                }       
            }
            // Second number's multiplier is bigger than first one's
            else if ((head_2->base) > (head_1->base))
            {
                if (!push_node(&temp_result, head_2->base, head_2->power))
                {
                    head_2 = head_2->next;
                }
                else
                {
                    free_list(temp_result);
                    return ALLOC_NODE_ERROR;
                }
            }
            // Both numbers have same prime multiplier
            else 
            {
                sum_power = head_1->power + head_2->power;
                if (!push_node(&temp_result, head_1->base, sum_power))
                {
                    head_1 = head_1->next;
                    head_2 = head_2->next;
                }
                else
                {
                    free_list(temp_result);
                    return ALLOC_NODE_ERROR;
                }
            }
        }
    }

#ifdef __DEBUG__
    printf("<REVERSED> RESULT:\n");
    print_list(stdout, temp_result);
#endif

    // Write result into `head_result`
    int32_t return_code = reverse_copy(temp_result, head_result);
    free_list(temp_result);

    return return_code;
}


// Square factorized number 
void square_factorized(node_t **const head)
{   
    node_t *temp_node = *head;

    // Simply double every multipliers's power (125 = 5^3 -> 125^2 = 5^(3 * 2))
    while (temp_node)
    {
        temp_node->power *= DOUBLE_POWER;
        temp_node = temp_node->next;
    }
}


// Divide two factorized numbers
// Division considers return factorized dividend & divisor back to the "normal"
// integers, divide them and factorize the result ((c) A.S. Kostritsky)
int32_t divide_factorized(const node_t *dividend, const node_t *divisor, node_t **const quotient)
{
    int32_t int_dividend = get_number(dividend);
    int32_t int_divisor = get_number(divisor);

    int32_t int_quotient = int_dividend / int_divisor;
    if (!int_quotient)
    {
        return DIVISION_ERROR;
    }

#ifdef __DEBUG__
    printf("DIVIDEND: %" PRId32 "  DIVISOR: %" PRId32 "\n", int_dividend, int_divisor);
    printf("QUOTIENT: %" PRId32 "\n", int_quotient);
#endif

    if (factorize_number(quotient, int_quotient))
    {
        return DIVISION_ERROR;
    }

    return SUCCESS;
}
