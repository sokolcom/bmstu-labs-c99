CC = gcc
CFLAGS = -std=c99 -Wall -Werror

DATA_PROC = data_processing
SORTS = sorts
TESTING = testing
DEBUG = debug

FUNC_C = $(wildcard src/*.c)
TEST = $(wildcard tests/*.c)

OBJ_SRC = $(patsubst %.c, %.o, $(wildcard $(FUNC_C)))
OBJ_TEST = $(patsubst %.c, %.o, $(wildcard $(TEST)))

HEADERS = ./include/define.h ./include/struct.h



app.exe: main.o $(OBJ_SRC)
	$(CC) -o $@ $^

test.exe: $(TESTING).o $(DATA_PROC)_testing.o $(SORTS).o $(OBJ_TEST)
	$(CC) -o $@ $^



# Release 
main.o: main.c ./include/$(DATA_PROC).h ./include/$(SORTS).h $(HEADERS)
	$(CC) $(CFLAGS) -c $<



# Module testing
$(TESTING).o: $(TESTING).c ./include/data_proc_test.h ./include/sorts_test.h ./include/tokens_test.h $(HEADERS)
	$(CC) $(CFLAGS) -c $<

$(DATA_PROC)_testing.o: ./src/$(DATA_PROC).c ./include/$(DATA_PROC).h $(HEADERS)
	$(CC) $(CFLAGS) -D _MODULE_TESTING_ -c $< -o $(DATA_PROC)_testing.o

$(SORTS).o: ./src/$(SORTS).c ./include/sorts.h $(HEADERS)
	$(CC) $(CFLAGS) -c $<



# Debug (program includes edebug prints)
debug.exe: $(DEBUG)_main.o $(DEBUG)_$(DATA_PROC).o $(SORTS).o
	$(CC) -o $@ $^

$(DEBUG)_main.o: main.c ./include/$(DATA_PROC).h ./include/$(SORTS).h $(HEADERS)
	$(CC) $(CFLAGS) -D _TESTING_ -c $< -o $(DEBUG)_main.o

$(DEBUG)_$(DATA_PROC).o: ./src/$(DATA_PROC).c ./include/$(DATA_PROC).h $(HEADERS)
	$(CC) $(CFLAGS) -D _TESTING_ -c $< -o $(DEBUG)_$(DATA_PROC).o



clean:
	rm *.o *.exe ./src/*.o ./tests/*.o