CC = gcc
CFLAGS = -std=c99 -Wall -Werror

app.exe: main.o matrix_cdio.o powers.o matrix_algebra.o
	$(CC) -o $@ $^

test.exe: testing.o matrix_cdio_testing.o powers.o matrix_algebra.o
	$(CC) -o $@ $^

main.o: main.c matrix_cdio.h powers.h matrix_algebra.h matrix_struct.h
	$(CC) $(CFLAGS) -c $<

matrix_cdio.o: matrix_cdio.c matrix_cdio.h matrix_struct.h
	$(CC) $(CFLAGS) -c $<

powers.o: powers.c powers.h
	$(CC) $(CFLAGS) -c $<

matrix_algebra.o: matrix_algebra.c matrix_algebra.h
	$(CC) $(CFLAGS) -c $<

testing.o: testing.c matrix_cdio.h powers.h matrix_algebra.h matrix_struct.h
	$(CC) $(CFLAGS) -c $<

matrix_cdio_testing.o: matrix_cdio.c matrix_cdio.h matrix_struct.h
	$(CC) $(CFLAGS) -D __TESTING__ -c $< -o matrix_cdio_testing.o

clean:
	rm *.o *.exe