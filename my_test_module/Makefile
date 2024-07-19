arch = x86
kernel_dir = /lib/modules/5.4.0-47-generic/build
pwd = $(shell pwd)
all:
	make -C $(kernel_dir) modules M=$(pwd) 
clean:
	make -C $(kernel_dir) clean M=$(pwd)
obj-m += my_test_module.o
