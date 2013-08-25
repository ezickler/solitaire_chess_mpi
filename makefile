CC = gcc
CFLAGS = -O2 -pedantic -Wall -Wextra -std=c99 `pkg-config --cflags --libs glib-2.0` .

all: solitaire_chess_mpi

solitaire_chess_mpi: main.o spielfiguren.o spielbretter.o askparam.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c main.h
	$(CC) $(CFLAGS) -c -o $@ $<

spielbretter.o: spielbretter.c spielbretter.h
	$(CC) $(CFLAGS) -c -o $@ $<
	
spielfiguren.o: spielfiguren.c spielfiguren.h
	$(CC) $(CFLAGS) -c -o $@ $<

askparam.o: askparam.c askparam.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f main.o spielfiguren.o spielbretter.o askparam.o solitaire_chess_mpi

.PHONY: clean
