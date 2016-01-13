all: server

server: server.c
	gcc -Wall $(shell sdl2-config --cflags) server.c -o server $(shell sdl2-config --libs) -lSDL2_net

clean:
	rm -f server
