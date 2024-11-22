ifeq ($(origin CC),default)
        CC = gcc
endif

FLAGS ?= -O0

.PHONY: final
final: problem_05.o
	$(CC) $^ -o $@

problem_05.o: problem_05.c
	$(CC) -Wno-unused-result -c $^ -o $@

.PHONY: clean
clean:
	rm *.o final
