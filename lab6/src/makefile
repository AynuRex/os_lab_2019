CC=gcc
CFLAGS= -std=c99 -w -lpthread -I./

all: client server

client : client.c libr.c libr.h
	$(CC) -o $@ $^ $(CFLAGS)

server :server.c libr.c libr.h
	$(CC) -o $@ $^ $(CFLAGS)

