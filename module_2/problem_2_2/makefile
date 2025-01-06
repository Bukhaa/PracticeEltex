ifeq ($(origin CC),default)
        CC = gcc
endif

FLAGS ?= -O2

COMMONINC = -I./include

override CFLAGS += $(COMMONINC)

.PHONY: all
all: calc.x

calc.x: calc.o main.o
	$(CC) $^ -o $@ $(LDFLAGS)

calc.o: ./source/calc.c
	$(CC)  $(CFLAGS)  -c $^ -o $@

main.o:  main.c
	$(CC)  $(CFLAGS)  -c $^ -o $@

.PHONY: clean
clean:
	rm *.o 
	rm calc.x
