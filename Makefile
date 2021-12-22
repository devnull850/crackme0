all: bytes copy test write
	./write

bytes: bytes.o
	ld -T bytes.ld -o bytes bytes.o

bytes.o: bytes.s
	as -o bytes.o bytes.s

copy: bytes
	dd if=bytes of=blob bs=1 skip=4118 count=48

test: test.c
	gcc -Wall -Werror -o test test.c

write: write.c
	gcc -Wall -Werror -o write write.c

.PHONY:
clean:
	rm bytes bytes.o blob test write
