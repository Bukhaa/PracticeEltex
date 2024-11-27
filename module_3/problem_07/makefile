ifeq ($(origin CC),default)
        CC = gcc
endif

FLAGS ?= -O0

.PHONY: all
all: server client
        

server.o: server.c
	$(CC) $(FLAGS) -Wno-unused-result -c $^ -o $@

server: server.o
	$(CC) -Wno-unused-result $^ -o $@

client.o: client.c
	$(CC) $(FLAGS) -Wno-unused-result -c  $^ -o $@

client: client.o
	$(CC) -Wno-unused-result $^ -o $@


.PHONY: clean
clean: 
	rm *.o server client
