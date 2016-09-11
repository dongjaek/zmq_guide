CXX=gcc
CFLAGS=-lzmq

all: dealer router 

dealer: dealer.c
	$(CXX) -o $@ $< $(CFLAGS)

router: router.c
	$(CXX) -o $@ $< $(CFLAGS)

clean:
	rm -f dealer router 
