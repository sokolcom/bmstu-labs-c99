CC = gcc
CFLAGS = -std=c99 -Wall -Werror

FUNC_C = $(wildcard *.c)
OBJ_SRC = $(patsubst %.c, %.o, $(wildcard $(FUNC_C)))

APP = app.exe


 
build: $(OBJ_SRC) $(OBJ_MAIN)
	$(CC) -o $(APP) $^


run: app.exe
	./app.exe


clean:
	rm -f *.o *.exe ./src/*.o