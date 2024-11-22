ifeq ($(origin CC),default)
        CC = gcc
endif

FLAGS ?= -O0

.PHONY: final
final: problem_04.o
	$(CC) $^ -o $@

problem_04.o: problem_04.c
	$(CC) -Wno-unused-result -c $^ -o $@

.PHONY: clean
clean:
	rm *.o final  
