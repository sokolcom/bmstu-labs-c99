#ifndef _DEFINE_H_
#define _DEFINE_H_


// Return codes
#define SUCCESS 0
#define TOKEN_ERROR 25
#define INPUT_ERROR 50
#define ALLOC_NODE_ERROR 75
#define EMPTY_LIST_ERROR 100
#define DIVISION_ERROR 125

#define TESTING_SUCCESS 0
#define TESTING_FAILURE 1


// Macroreplacements
#define MAX_STR_LENGTH 256

// Check if list empty
#define EMPTY 1
#define NOT_EMPTY -1

// fscanf() return codes
#define ONE_VAR 1
#define TWO_VARS 2
#define MIN_VALUE 1  // minimal value to be entered
#define DOUBLE_POWER 2  // multiply power by two to get squared number

// Operating modes (user input)
#define OUTPUT "out"
#define MULTIPLICATION "mul"
#define SQUARE "sqr"
#define DIVIDE "div"

// Operating modes' tokens
#define TOKEN_OUT 1
#define TOKEN_MUL 2
#define TOKEN_SQR 3
#define TOKEN_DIV 4
#define UNKNOWN_TOKEN -1

// Testing
#define PASSED 1
#define FAILED 0
#define TESTS_AMOUNT 17

#define INCORRECT_RESULT 0
#define CORRECT_RESULT 1

#endif
