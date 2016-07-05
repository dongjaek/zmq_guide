#include <zmq.h>
#include <assert.h> //assert
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv) {

	printf("STARTING THE CLIENT");

	// Create a context for a socket and make it a subscriber to whatever is coming out of 5556
	void *context = zmq_ctx_new();
	void *subscriber = zmq_socket(context, ZMQ_SUB);
	int rc = zmq_connect(subscriber, "tcp://localhost:5556");
	// assert will close the process and flush the streams that are open.
	assert(rc == 0);

	// Configure the socket
	char *filter = (argc > 1) ? argv[1] : "10001 ";
	// filter allows only 
	rc = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, filter, strlen(filter));	
	assert(rc == 0);

	// Each subscriber receives 100 updates from the weather server 
	int update_nbr;
	long total_temp = 0;
	for (update_nbr = 0; update_nbr < 100; update_nbr++) { 
		// Receive a string
		char buffer[256];
		int size = zmq_recv(subscriber, buffer, 255, 0); //255 to account for a one byte null
		if (size == -1) continue; // dud string receive
		if (size > 255) size = 255;	
		buffer[size] = 0;
		
			
		int zipcode, temperature, relhumidity;	
		sscanf(buffer, "%d %d %d", &zipcode, &temperature, &relhumidity);
		total_temp += temperature;
	}	

	// Output the average
	printf("Average temp for zipcode '%s' was %dF\n", filter, (int)(total_temp/update_nbr));

	zmq_close(subscriber);
	zmq_ctx_destroy(context);
	printf("CLIENT DESTROYED");
	return 0;
}

/*
	Q. What is the difference between connect and bind? Aside from when the queue is created (eager/lazy). Are there restrictions on each method of incoming/outgoing messages?
	Q. How does the filter work? "10001" is filtering based on what? port? How does this arbitrary string get used in the actual filtering process in relation to an IP?
	Q. Why are sockets void pointers instead of structs?	
*/
