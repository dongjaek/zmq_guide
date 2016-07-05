#include <zmq.h>
#include <assert.h> //assert
#include <stdlib.h> //srandom
#include <string.h> //strlen
#include <time.h>   //time

#define randof(num)  (int) ((float) (num) * random () / (RAND_MAX + 1.0))

int main() {

	printf("STARTING THE SERVER");

	// Create a context
	void *context = zmq_ctx_new();
	// Create a socket from the context of the publisher role
	void *publisher = zmq_socket(context, ZMQ_PUB);
	int rc = zmq_bind(publisher, "tcp://*:5555");
	assert( rc = 0 );
	rc = zmq_bind(publisher, "ipc://weather.ipc");
	assert ( rc = 0 );	

	// Generate infinite random numbers and publish them to all listening subscribers
	srandom( (unsigned) time(NULL) );
	while(1) {
		int zipcode, temperature, relhumidity;
		zipcode = randof(100000);
		temperature = randof(215) - 80;
		relhumidity = randof(50) + 10;

		char update[20];
		sprintf(update, "%05d %d %d", zipcode, temperature, relhumidity);
    int size = zmq_send (publisher, update, strlen(update), 0);
		if (size == -1) continue;
	}

	zmq_close(publisher);
	zmq_ctx_destroy(context);
	printf("SERVER CLOSED");
	return 0;
}
