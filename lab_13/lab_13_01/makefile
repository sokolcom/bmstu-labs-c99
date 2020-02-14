CC = gcc
CFLAGS = -std=c99 -Wall -Werror

LIB_REV = librev


REV_SRC = $(wildcard src/*_link.c)
REV_DYNAMIC = $(wildcard src/*_upload.c)
REV_TESTS = $(wildcard *_test.c)
 
OBJ_STATIC = $(patsubst %.c, %.o, $(wildcard $(REV_SRC)))
OBJ_DYNAMIC = $(patsubst %.c, %.o, $(wildcard $(REV_DYNAMIC)))
OBJ_TESTS = $(patsubst %.c, %.o, $(wildcard $(REV_TESTS)))
OBJ_DLL = rev_link_dll.o



# Make all libs
all_lib: dll static

dll: $(LIB_REV).so
static: $(LIB_REV).a



# Testing
test.exe: $(OBJ_TESTS)
	$(CC) -o $@ $^

# Test .so call in c-file
c_dll: $(OBJ_DYNAMIC)
	$(CC) -o $@ $^




$(LIB_REV).a: $(OBJ_STATIC)
	ar rc  $@  $^

$(LIB_REV).so: $(OBJ_DLL)
	$(CC) -shared -o $@ $^


$(OBJ_DLL): $(REV_SRC) 
	$(CC) -fPIC -o $(OBJ_DLL) -c $^



clean:
	rm *.o *.so *.a
