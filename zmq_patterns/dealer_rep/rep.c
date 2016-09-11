#include <zmq.h>
#include <stdio.h>  //printf
#include <assert.h> //assert
#include <errno.h>  //errno
#include <string.h> //strerro

#define checkError( err ) { 																							\
	if( err == -1 ) printf("%s\n", strerror( errno )); assert( err != -1 ); \
} 																																				\

int main() {

	int err = 0;
	// Create ZMQ environment
	void* ctx = zmq_ctx_new();
	void* request = zmq_socket(request, ZMQ_DEALER);
	zmq_connect(request, "tcp://*:8080");

	// Receive an infinite stream of messages
	int num = 0;
	while(1) {
		printf("RECEIVING MESSAGE: %d\n", num);
		num++;
		zmq_msg_t msg;
		err = zmq_msg_init_size(&msg, 5);
		checkError( err );
		err = zmq_msg_send(&msg, request, 0);
		checkError( err );
		err = zmq_msg_close(&msg);
		checkError( err );
	}

	// Destroy ZMQ environmetn
	err = zmq_close(request);
	checkError( err );
	err = zmq_ctx_destroy(ctx);
	checkError( err );
}
