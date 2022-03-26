streaming between the server and the client could be implemented by more than mehtod.
And the proposed options are 
1- Http pooling between the server and the client
2- gRPC server push
3- via message queueing system

I choosed the message queueing system in order to remove the headech of the communication with client from the server. And transfer it to the queueing system. the message queueing system is effiecient in the case of IOT.
