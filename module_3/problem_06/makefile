ifeq ($(origin CC),default)
        CC = gcc
endif

FLAGS ?= -O0

.PHONY: all
all: serv cl
	

serv.o: serv.c
	$(CC) -Wno-unused-result -c $^ -o $@

serv: serv.o
	$(CC) -Wno-unused-result $^ -o $@

cl.o: cl.c
	$(CC) -Wno-unused-result -c  $^ -o $@

cl: cl.o
	$(CC) -Wno-unused-result $^ -o $@


.PHONY: clean
clean: 
	rm *.o serv cl
