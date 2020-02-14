CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic

app.exe: main.o array_cdio.o compute_mu.o p_number.o
	$(CC) -o $@ $^

test.exe: testing.o array_cdio.o compute_mu.o p_number.o
	$(CC) -o $@ $^

main.o: main.c array_cdio.h compute_mu.h p_number.h
	$(CC) $(CFLAGS) -c $<

arary_cdio.o: array_cdio.c array_cdio.h
	$(CC) $(CFLAGS) -c $<

compute_mu.o: compute_mu.c compute_mu.h
	$(CC) $(CFLAGS) -c $<

p_number.o: p_number.c p_number.h
	$(CC) $(CFLAGS) -c $<

testing.o: testing.c array_cdio.h compute_mu.h p_number.h
	$(CC) $(CFLAGS) -c $<
	
clean:
	rm *.o *.exe