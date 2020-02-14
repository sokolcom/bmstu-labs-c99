#ifndef _DEFINE_H_
#define _DEFINE_H_

// Return code
#define SUCCESS 0
#define TESTING_SUCCESS 0

#define ALLOC_ERROR 100
#define INPUT_ERROR 200
#define DELETE_ERROR 300
#define TOKEN_ERROR 500
#define OUT_STREAM_ERROR 600
#define TESTING_FAILURE 1

// Macroreplacements
#define MAX_STR_LEN 256  // max string length

// Input flag (do input or stop)
#define INPUT_OK 1
#define INPUT_STOP 0

// Compare article to "nothing" in any case (e.g. "nOTHinG")
#define CONTINUE_INPUT 1
#define ABORT_INPUT 0

// strcmp() return code 
#define SAME_STR 0

// "Distance" between letter in lowercase and uppercase ('a' - 'A' = 32)
#define CHANGE_CASE 32

// User input sorting tokens
#define ARTICLE "ARTICLE"
#define NAME "NAME"
#define COUNT "COUNT"

// Sorting token
#define TOKEN_ARTICLE 1
#define TOKEN_NAME 2
#define TOKEN_COUNT 3
#define UNKNOWN_TOKEN -1  // no match to existing tokens

// Comparator results
#define FIRST_ARG 1
#define SECOND_ARG -1
#define EQUAL_ARG 0

// Is item array sorted before completing cycle? 
#define SORTED 1
#define NOT_SORTED 0

// Check entered data return codes & testing codes
#define PASSED 1
#define FAILED 0

// Compare two stocks
#define DIFFERENT_DATA 0
#define SAME_DATA 1

// Memory allocation testing
#define MEMORY_TEST 1
#define NORMAL_TEST 0

#endif
