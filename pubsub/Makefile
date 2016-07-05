CC=gcc

EXEC=server client

all: $(EXEC)

server:
	$(CC) server.c -lzmq -o $@

client:
	$(CC) client.c -lzmq -o $@

clean:
	rm -f client server
