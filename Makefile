CFLAGS=-std=c11 -g -static
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

slcc: $(OBJS)
	$(CC) -o slcc $(OBJS) $(LDFLAGS)

$(OBJS): slcc.h

test: slcc
	./test.sh

clean:
	rm -f slcc *.o *~ tmp*

.PHONY: test clean
