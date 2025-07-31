obj-m += sandbox.o
obj-m += permission_control.o
obj-m += signature_verification.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean 