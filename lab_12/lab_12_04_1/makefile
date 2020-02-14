CC = gcc
CFLAGS = -std=c99 -Wall -Werror

MAIN = main
TESTMAIN = testing
MATHS = arithmetics
DEBUG = debug
DDEBUG = __DEBUG__

FUNC_C = $(wildcard src/*.c)
SRC_DEBUG = $(wildcard src/*e.c src/tokens.c)  # All .c except arithmetics.c
TEST = $(wildcard tests/*.c)

OBJ_MAIN = $(patsubst %.c, %.o, $(MAIN).c)
OBJ_TESTMAIN = $(patsubst %.c, %.o, $(TESTMAIN).c)
OBJ_SRC = $(patsubst %.c, %.o, $(wildcard $(FUNC_C)))
OBJ_TEST = $(patsubst %.c, %.o, $(wildcard $(TEST)))

# All objects except arithmetics.o (separate due to -D)
OBJ_DEBUG = $(patsubst %.c, %.o, $(wildcard $(SRC_DEBUG)))

HEADERS = ./include/define.h ./include/struct.h ./include/list_interface.h ./include/$(MATHS).h



app.exe: $(OBJ_SRC) $(OBJ_MAIN)
	$(CC) -o $@ $^

test.exe: $(OBJ_SRC) $(OBJ_TEST) $(OBJ_TESTMAIN)
	$(CC) -o $@ $^


# Debug (program includes debug prints)
debug.exe: $(OBJ_MAIN) $(OBJ_DEBUG) $(DEBUG)_$(MATHS).o 
	$(CC) -o $@ $^

$(DEBUG)_$(MATHS).o: ./src/$(MATHS).c  $(HEADERS)
	$(CC) $(CFLAGS) -D $(DDEBUG) -o $@ -c $<



clean:
	rm *.o *.exe ./src/*.o ./tests/*.o
