ifeq ($(origin CC),default)
        CC = gcc
endif

FLAGS ?= -O0

COMMONINC = -I./include

override FLAGS += $(COMMONINC)


.PHONY: all
all: final sum.so sub.so mul.so divis.so sum.o sub.o mul.o divis.o

.PHONY: final
final:  main.o 
	$(CC)  $^ -o $@ -ldl 

main.o: main.c
	$(CC) -Wno-unused-result $(FLAGS)  -c $^ -o $@ 

sum.o: sum.c
	$(CC) -fPIC -Wno-unused-result $(FLAGS)  -c $^ -o $@

sub.o: sub.c
	$(CC) -fPIC -Wno-unused-result $(FLAGS)  -c $^ -o $@

mul.o: mul.c
	$(CC) -fPIC -Wno-unused-result $(FLAGS)  -c $^ -o $@

divis.o: divis.c
	$(CC) -fPIC -Wno-unused-result $(FLAGS)  -c $^ -o $@

sum.so: sum.o
	$(CC) -shared $^ -o $@

sub.so: sub.o
	$(CC) -shared $^ -o $@

mul.so: mul.o
	$(CC) -shared $^ -o $@

divis.so: divis.o
	$(CC) -shared $^ -o $@ 

clean:
	rm *.o *.so final

