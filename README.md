## Choosing Streaming Protocol
streaming between the server and the client could be implemented by more than mehtod.
And the proposed options are 
1. Http pooling between the server and the client
2. Http Websocit
3. gRPC server push
4. message queueing system (using non-durable topics)

I choosed the message queueing system in order to remove the headech of the communication with client from the server. And transfer it to the queueing system. the message queueing system is effiecient in the case of IOT.

## Run the solution
> bash -x run.sh

This command will run the activemq image, run the server, and run the client
