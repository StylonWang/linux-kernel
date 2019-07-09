KERNEL_VER=`uname -r`
KERNEL_DIR=/lib/modules/$(KERNEL_VER)/build
PWD=`pwd`

obj-m := kthread.o

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean


