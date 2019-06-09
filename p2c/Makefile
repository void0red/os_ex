obj = p2c_1.o
CC = gcc
CFLAGS = -O3 -Wall -s
LDFLAGS = -l pthread
p2c_1:$(obj)
	$(CC) $(CFLAGS) $(obj) -o p2c_1 $(LDFLAGS)

p2c_1.o:p2c_1.c
	@$(CC) $(CFLAGS) -c p2c_1.c

clean:
	@rm -rf $(obj) p2c_1
