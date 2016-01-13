all: client

client: client.c
	gcc -Wall $(shell sdl2-config --cflags) client.c -o client $(shell sdl2-config --libs) -lSDL2_net
    
clean:
	rm -f client
