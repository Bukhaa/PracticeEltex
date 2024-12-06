ifeq ($(origin CC),default)
        CC = gcc
endif

FLAGS ?= -O0

.PHONY: all
all: server client
	

server.o: server.c
	$(CC) -c $^ -o $@

server: server.o
	$(CC)  $^ -o $@

client.o: client.c
	$(CC) -c  $^ -o $@

client: client.o
	$(CC)  $^ -o $@


.PHONY: clean
clean: 
	rm *.o server client
