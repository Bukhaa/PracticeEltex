ifeq ($(origin CC),default)
        CC = gcc
endif

FLAGS ?= -O0

COMMONINC = -I./include

override FLAGS += $(COMMONINC)


.PHONY: final
final: contact_list.o bst.o main.o 
	$(CC)  $^ -o $@ $(LDFLAGS)

bst.o:  ./source/bst.c
	$(CC) -Wno-unused-result $(FLAGS)  -c $^ -o $@

contact_list.o: ./source/contact_list.c
	$(CC) -Wno-unused-result $(FLAGS)  -c $^ -o $@

main.o: ./main.c
	$(CC) -Wno-unused-result $(FLAGS)  -c $^ -o $@

.PHONY: clean
clean:
	rm *.o final
