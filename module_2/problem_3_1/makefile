ifeq ($(origin CC),default)
        CC = gcc
endif

FLAGS ?= -O2

COMMONINC = -I./include

override CFLAGS += $(COMMONINC)

chmod.x: chmod.o
	$(CC) $^ -o $@ $(LDFLAGS)

chmod.o:  chmod.c
	$(CC)  $(CFLAGS)  -c $^ -o $@

.PHONY: clean
clean:
	rm chmod.x
	rm chmod.o
