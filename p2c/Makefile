obj = p2c.o
CC = gcc
CFLAGS = -O3 -Wall -s
LDFLAGS = -l pthread
sort:$(obj)
	$(CC) $(CFLAGS) $(obj) -o p2c $(LDFLAGS)

p2c.o:p2c.c
	@$(CC) $(CFLAGS) -c p2c.c

clean:
	@rm -rf $(obj) p2c
