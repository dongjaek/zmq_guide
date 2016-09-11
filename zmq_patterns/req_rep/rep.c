#include <zmq.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define checkError( err ) { 																						\
	if( err == -1 ) printf("%s\n", strerror( errno )); assert( err != -1 ); \
} 																																			\

int main () {

	void *ctx = zmq_ctx_new();
	void *reply = zmq_socket(ctx, ZMQ_REP);
	int err = 0;
	//err = zmq_connect(reply, "tcp://*:8080"); // A REP socket requires a fixed endpoint
	err = zmq_bind(reply, "tcp://172.17.0.2:8080");  // a REP socket should have a bind
	checkError( err );

	// Send messages to a rep socket in lockstep
	int num = 0;
	while(1) {
		printf("Receiving request : %d\n", num);
		zmq_msg_t req;
		err = zmq_msg_init_size(&req, 6);
		checkError( err );
		err = zmq_msg_recv(&req, reply, 0);
		checkError( err );
		err = zmq_msg_close(&req);
		checkError( err );

		printf("Replying to request : %d\n", num);
		zmq_msg_t rep;
		err = zmq_msg_init_size(&rep, 6);
		checkError( err );
		sprintf(zmq_msg_data(&rep), "%s", "World");
		err = zmq_msg_send(&rep, reply, 0);
		checkError( err );
		err = zmq_msg_close(&rep);
		checkError( err );

		num++;
	}

	err = zmq_close(reply);
	checkError( err );
	err = zmq_ctx_destroy(ctx);
	checkError( err );
}
