#!/usr/bin/python

""" 
Note that in order to make this work with Matlab one needs to wait a bit
between opening the connection and sending data to the server, otherwise
the server fails to read the data:

cf. http://stackoverflow.com/questions/20271970/matlab-sockets-wait-for-response

Alexandre Lopes (adapted from Python's docs)
22.07.2015

To Do: Catch exceptions
"""


# Echo client program
import socket
import time

HOST = ''                 # The remote host
PORT = 59263              # The same port as used by the server
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
time.sleep(1)             # Workaround for Matlab

while 1:
    input = raw_input('>')
    
    if input == "quit":
        break

    if input == "exit":
        s.sendall(input)
        break

    elif input == "echo":
        s.sendall(input)
        data = s.recv(1024)
        print 'Received', repr(data)

    else:
        s.sendall(input)
    

s.close()
