CC = gcc
CFLAGS = -std=c99 -Wall -Werror


C_ALL = $(wildcard *.c)
OBJ_ALL = $(patsubst %.c, %.o, $(wildcard $(C_ALL)))



test.exe: $(OBJ_ALL)
	$(CC) -o $@ $^


clean:
	rm *.o *.exe

