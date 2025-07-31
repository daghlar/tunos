obj-m += location_control.o
obj-m += network_control.o
obj-m += sensor_control.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean 