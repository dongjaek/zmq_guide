CXX=gcc
CFLAGS=-lzmq

all: req router 

req: req.c
	$(CXX) -o $@ $< $(CFLAGS)

router: router.c
	$(CXX) -o $@ $< $(CFLAGS)

clean:
	rm -f req router 
