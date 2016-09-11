CC=gcc
CFLAGS=-lzmq

all: dealer rep

dealer: dealer.c
	$(CC) -o $@  $< $(CFLAGS)

rep: rep.c
	$(CC) -o $@  $< $(CFLAGS)

clean:
	rm -f dealer rep
