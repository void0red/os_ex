obj = sort.o
CC = gcc
CFLAGS = -O3 -Wall -s
LDFLAGS = -IL /usr/lib/libpthread.so
sort:$(obj)
	$(CC) $(CFLAGS) $(obj) -o sort $(LDFLAGS)

sort.o:sort.c
	@$(CC) $(CFLAGS) -c sort.c

clean:
	@rm -rf $(obj) sort
