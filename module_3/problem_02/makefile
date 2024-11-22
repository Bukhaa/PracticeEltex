ifeq ($(origin CC),default)
        CC = gcc
endif

FLAGS ?= -O0

.PHONY: all
all: final max_arg sum_args

.PHONY: final
final: problem_02.o 
	$(CC) $^ -o $@

problem_02.o: problem_02.c
	$(CC) -Wno-unused-result -c $^ -o $@

sum_args.o: sum_args.c
	$(CC) -Wno-unused-result -c $^ -o $@

sum_args: sum_args.o
	$(CC) -Wno-unused-result $^ -o $@

max_arg.o: max_arg.c
	$(CC) -Wno-unused-result -c  $^ -o $@

max_arg: max_arg.o
	$(CC) -Wno-unused-result  $^ -o $@

.PHONY: clean
clean:
	rm *.o final max_arg sum_args
