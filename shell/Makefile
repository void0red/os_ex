obj = shell.o
CC = gcc
CFLAGS = -O3 -Wall -s
shell: $(obj)
	$(CC) $(CFLAGS) -o shell $(obj)

shell.o: shell.c
	@$(CC) $(CFLAGS) -c shell.c

clean:
	@rm shell $(obj) -rf
