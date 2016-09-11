#include <zmq.h>
#include <stdio.h>  //printf
#include <assert.h> //assert
#include <errno.h>  //errno
#include <string.h> //strerro

#define checkError( err ) { 															\
	if( err == -1 ) strerror( errno ); assert( err != -1 ); \
} 																												\

int main() {

	int err = 0;
	// Create ZMQ environment
	void* ctx = zmq_ctx_new();
	void* dealer = zmq_socket(dealer, ZMQ_DEALER);
	zmq_connect(dealer, "tcp://172.17.0.2:8080");

	// Send an infinite stream of messages
  int num = 0;
	while(1) {
		printf("SENDING MESSAGE: %d\n", num);
		num++;
		zmq_msg_t msg;
		err = zmq_msg_init_size(&msg, 5);
		printf("%d\n", err);
		checkError( err );
		err = zmq_msg_send(&msg, dealer, 0);
		checkError( err );
		err = zmq_msg_close(&msg);
		checkError( err );
	}

	// Destroy ZMQ environmetn
	err = zmq_close(dealer);
	checkError( err );
	err = zmq_ctx_destroy(ctx);
	checkError( err );
}
