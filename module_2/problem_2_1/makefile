ifeq ($(origin CC),default)
        CC = gcc
endif

FLAGS ?= -O2

COMMONINC = -I./include

override CFLAGS += $(COMMONINC)

.PHONY: all
all: contact_list.x

contact_list.x: contact_list.o main.o
	$(CC) $^ -o $@ $(LDFLAGS)

contact_list.o: ./source/contact_list.c
	$(CC)  $(CFLAGS)  -c $^ -o $@

main.o:  main.c
	$(CC)  $(CFLAGS)  -c $^ -o $@

.PHONY: clean
clean:
	rm *.o 
	rm contact_list.x
