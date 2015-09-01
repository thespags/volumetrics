CC=gcc
CFLAGS=-Wall -g -lcurses

all: spin

spin: main.c yahtzee.c score.c draw.c sheet.c
	$(CC) $(CFLAGS) main.c yahtzee.c score.c draw.c sheet.c -o spin

clean:
	rm -rf *o spin
