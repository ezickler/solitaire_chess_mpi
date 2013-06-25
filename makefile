CFLAGS=-Wall -Werror -O3

%.x:%.c
	${CC} ${CFLAGS} -o $@ $<

clean:
	rm -f *.o *.x
