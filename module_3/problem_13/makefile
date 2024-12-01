ifeq ($(origin CC),default)
        CC = gcc
endif

FLAGS ?= -O0

main.x: main.c
	$(CC) $(FLAGS) -lrt $^ -o $@

.PHONY: clean
clean: 
	rm main.x 
