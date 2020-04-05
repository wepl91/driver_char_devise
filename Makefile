obj-m := driver_module.o

all: read write
	make -C /lib/modules/$(shell uname -r)/build SUBDIRS=$(shell pwd) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build SUBDIRS=$(shell pwd) clean
	rm read
	rm write
read:
	cc     read.c -o read
write:
	cc     write.c -o write

test:
	rm -f test.txt
	./write test.txt prueba
	./read test.txt 2
	./read test.txt 4 2