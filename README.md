# Group-Chat
It is a C based program build on the concepts of Socket Programming.

In which we can join many client to a server and can share messages between each other and form a group for chatting.

In this project, server provides a unique ID's to each client which get connected to it and work as a routing medium
between all of them for share conversations and monitoring them.

## Implementation
1. Compile both of the file [client.c](https://github.com/AkiiSinghal/Group-Chat/blob/master/client.c) and [server.c](https://github.com/AkiiSinghal/Group-Chat/blob/master/server.c) using gcc compiler by typing.
   * gcc client.c -pthread -o client
   * gcc server.c -pthread -o server
2. The most important condition to use socket programming is that all the devices are on same network.
3. Run the server file on the system which will be use as a server.
   * ./server
4. Now run the client program on the system which will be use as a client.
   * ./client <server's_IP_address>
     * __Note:__ You can check ip using **ifconfig -a** in linux.
     * If you are using server and client on same system use *127.0.0.1* as your local IP.
     
## Screenshots
![1](https://user-images.githubusercontent.com/42001728/62043203-63d1cb80-b21d-11e9-90e9-80e03c43ac18.png)
![2](https://user-images.githubusercontent.com/42001728/62043205-63d1cb80-b21d-11e9-8c14-2bdaac036156.png)
