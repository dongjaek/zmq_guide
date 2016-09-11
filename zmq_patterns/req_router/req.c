#include <zmq.h>
#include <string.h> //strerror
#include <assert.h> //assert
#include <stdio.h>  //printf
#include <errno.h>  //errno

#define checkError( err ) { 																							\
	if( err == -1 ) printf("%s\n", strerror( errno )); assert( err != -1 ); \
} 																																				\

int main() {

	void* ctx = zmq_ctx_new();
	void* request = zmq_socket(ctx, ZMQ_REQ);
	int err = 0;
	err = zmq_connect(request, "tcp://172.17.0.2:8080");

	int num = 0;
	while(1) {
		printf("REQ : Sending message : %d\n", num);
		zmq_msg_t msg;
		err = zmq_msg_init_size(&msg, 6);
		checkError( err );
		err = zmq_msg_send(&msg, request, 0);
		checkError( err );
		err = zmq_msg_close(&msg);
		checkError( err );

		printf("REQ : Receiving message : %d\n", num);
		zmq_msg_t rep;
		err = zmq_msg_init_size(&rep, 6);
		checkError( err );
		err = zmq_msg_recv(&rep, request, 0);
		checkError( err );
		err = zmq_msg_close(&rep);
		checkError( err );
	
		num++;
	}

	zmq_close(request);
	zmq_ctx_destroy(ctx);
}
