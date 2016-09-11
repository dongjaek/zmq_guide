Terminology:

Frames == message-part == one zmq_msg_t structure.
Each frame is sent individually.



Message, can be single or multi-part. Compose of frames

Multipart message composed of three frames
zmq_msg_send (&message, socket, ZMQ_SNDMORE);
...
zmq_msg_send (&message, socket, ZMQ_SNDMORE);
...
zmq_msg_send (&message, socket, 0);


