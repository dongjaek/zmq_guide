CXX=gcc
CFLAGS=-lzmq

all: req rep

req: req.c
	$(CXX) -o $@ $< $(CFLAGS)

rep: rep.c
	$(CXX) -o $@ $< $(CFLAGS)

clean:
	rm -f req rep
