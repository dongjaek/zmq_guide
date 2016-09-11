Request <-> Reply

Request Reply work in lockstep: 
Request initiated with a send which is non-blocking as the message gets stuffed in the queue
Request should then wait on a blocking recv 

Reply waits on a blocking recv
Reply sends a non-blocking message in the message queue

Always run the server container first.
