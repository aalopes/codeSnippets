Here are some examples of TCP/IP servers and clients for several languages.
Most of them are small adaptations of code in the open domain. They should
work with each other and should be easy to use in real software with some small 
modifications.

Here's what they do:
    Client: Sends a string to the server. Special commands: 
        "quit" - tells server to terminate connection and closes client
        "exit" - closes client and server
        "echo" - listens to server reply (only python and matlab)
    
    Server: Loops infinitely, waiting for clients to connect. Whenever a client
    connects, print to screen.

Note that the degree to which errors and how complex the implementation is,
varies a lot between servers and clients, as these are only simple examples.
Also, I haven't implemented the echo functionality in the C code.

For TCP/UDP the examples would need minor modifications.

Alexandre Lopes

11.01.2016
