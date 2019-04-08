KERNEL_VER=`uname -r`
KERNEL_DIR=/usr/src/linux-headers-$(KERNEL_VER)
PWD=`pwd`

obj-m := kthread.o

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean


