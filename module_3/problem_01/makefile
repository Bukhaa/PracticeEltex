ifeq ($(origin CC),default)
        CC = gcc
endif

FLAGS ?= -O0

.PHONY: final
final: problem_01.o
	$(CC) $^ -o $@

problem_01.o: problem_01.c
	$(CC) -Wno-unused-result -c $^ -o $@

.PHONY: clean
clean: 
	rm *.o final
