CFLAGS=-std=c11 -g -static

slcc: slcc.c

test: slcc
	./test.sh

clean:
	rm -f slcc *.o *~ tmp*

.PHONY: test clean
