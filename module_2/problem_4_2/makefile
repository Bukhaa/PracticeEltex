ifeq ($(origin CC),default)
        CC = gcc
endif

FLAGS ?= -O2

COMMONINC = -I./include

override CFLAGS += $(COMMONINC)

main.x: main.o
	$(CC) $^ -o $@ $(LDFLAGS)

main.o:  main.c
	$(CC)  $(CFLAGS)  -c $^ -o $@

.PHONY: clean
clean:
	rm main.x
	rm main.o
