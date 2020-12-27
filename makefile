all: server client 


server: server.c sh.h sh.c
	gcc -o server server.c sh.c

client: client.c ch.h ch.c
	gcc -o client client.c ch.c
