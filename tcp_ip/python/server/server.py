#!/usr/bin/python

""" TCP/IP server

Alexandre Lopes
15.12.2015

"""

import select
import socket
import time
import signal
import sys
import locale

from difflib import Differ


# functions -------------------------------------------------------------------

def sigintHandler(signal, frame):
    """
    SIGINT Handler in case user presses ctr+c - in order to close the 
    server gracefully.
    We do not disconnect the client since that would imply knowing whether
    or not a client connect and seems unnecessary for our purposes.
    """
    print ('\nCtrl+C pressed! Shutting down server.')
    sys.exit(0)

# declarations ----------------------------------------------------------------
    
HOST    = ''          # Symbolic name meaning all available interfaces
PORT    = 59263       # Arbitrary non-privileged port
TIMEOUT =  60      # Timeout (s)

# main ------------------------------------------------------------------------

print ('Server started ...')

# register interrupt handler
signal.signal(signal.SIGINT, sigintHandler)

# create socket and bind to the right port
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))


# listen to connections
s.listen(1)

# server loop
quitServer = 0 
while quitServer != 1:

    # accept incoming connection
    # as it stands if another connection is attempted, it will replace
    # the previous one. Therefore use only 1 client at a time!

    conn, addr = s.accept()
    print ('Client on ', addr, ' connected.')

    # loop to read data from our socket
    while 1:
        # receive incoming data only if there is data to be received!
        # this way we can timeout if the client hangs for some reason,
        # avoid getting stuck at conn.recv and move to accept a new connection
        ready = select.select([conn], [], [], TIMEOUT)
        if ready[0]:
            data = conn.recv(1024)

            if not data:
                print ('Client closed socket!')
                break
            else:
                # data parsing ---------
                # remove trailling null bytes (C)
                data = data.rstrip('\0')
                data = data.rstrip('\x00')

                # perform execute
                if data == 'quit':
                   
                    conn.close()
                    print ('Client disconnected.')

                elif data == 'exit':
                    print("Closing server!")
                    quitServer = 1
                    break
                    
                elif data == 'echo':
                    print (data)
                    # echo
                    conn.sendall('echo')
                    
                else:
                    print (data)

        else:
            print ('Client timed out!')
            break

