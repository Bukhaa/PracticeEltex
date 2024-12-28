obj-m += kernel_space.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc -O2 user_space.c -o user_space

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm user_space
