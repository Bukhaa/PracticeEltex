# FLAGS = -O0 by default
# make -f makefile clean
# make -f makefile


ifeq ($(origin CC),default)
        CC = gcc
endif

FLAGS ?= -O0

COMMONINC = -I./include

override FLAGS += $(COMMONINC)


.PHONY: final
final: contact_list.o main.o dlist_lib 
	$(CC) -L . $^ -o $@ $(LDFLAGS)

dlist.o: ./source/dlist.c
	$(CC) -Wno-unused-result $(FLAGS)  -c $^ -o $@

main.o:  main.c
	$(CC) -Wno-unused-result $(FLAGS)  -c $^ -o $@

contact_list.o: ./source/contact_list.c
	$(CC) -Wno-unused-result $(FLAGS)  -c $^ -o $@

dlist_lib: dlist.o
	ar -cr  dlist_lib $^
	
.PHONY: clean
clean:
	rm *.o final
