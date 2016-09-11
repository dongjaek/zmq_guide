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
	void* router = zmq_socket(ctx, ZMQ_ROUTER);
	int err = 0;
	err = zmq_bind(router, "tcp://*:8080");

	int num = 0;
	while(1) {
		printf("ROUTER: Receiving message : %d\n", num);
		zmq_msg_t rep;
		err = zmq_msg_init_size(&rep, 6);
		checkError( err );
		err = zmq_msg_recv(&rep, router, 0);
		checkError( err );

		printf("%s\n", (char*)zmq_msg_data(&rep));

		err = zmq_msg_close(&rep);
		checkError( err );

		printf("ROUTER: Sending message : %d\n", num);
		zmq_msg_t msg;
		err = zmq_msg_init_size(&msg, 6);
		checkError( err );
		err = zmq_msg_send(&msg, router, 0);
		checkError( err );
		err = zmq_msg_close(&msg);
		checkError( err );

		num++;
	}

	zmq_close(router);
	zmq_ctx_destroy(ctx);
}
