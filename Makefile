obj-m += st_kernel.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 
	gcc use_kernel.c -o use_kernel
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	gcc use_kernel.c -o use_kernel clean
