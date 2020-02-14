CC = gcc
CFLAGS = -std=c99 -Wall -Werror

APP_NAME = app.exe
FILENAME = in.txt

FUNC_C = $(wildcard *.c)

OBJ_SRC = $(patsubst %.c, %.o, $(FUNC_C))


build: $(OBJ_SRC)
	$(CC) -o $(APP_NAME) $^

run:
	./$(APP_NAME) $(FILENAME)


clean:
	rm *.o *.exe

