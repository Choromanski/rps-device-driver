obj-m := rps_dev.o 

export PATH:=$(PATH):/usr/bin:/usr/lib/gcc/i486-linux-gnu/4.6
export LD_LIBRARY_PATH:=$(LD_LIBRARY_PATH):/usr/lib/i386-linux-gnu

KDIR  := /lib/modules/3.2.0-4-686-pae/build
PWD   := $(shell pwd)

default: rps_dev.ko rps_ctrl rps

rps_dev.ko: rps_dev.c  rps_dev.h
	$(MAKE) -C $(KDIR) M=$(PWD) PATH=$(PATH) LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) modules
	
rps_ctrl: rps_ctrl.c
	gcc -m32 rps_ctrl.c -o rps_ctrl

rps: rps.c
	gcc -m32 rps.c -o rps


clean:
	$(MAKE) -C $(KDIR) M=$(PWD) PATH=$(PATH) LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) clean
	rm rps_ctrl rps
