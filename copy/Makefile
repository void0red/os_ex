obj = copy.o
CC = gcc
CFLAGS = -O3 -Wall -s
copy:$(obj)
	$(CC) $(CFLAGS) $(obj) -o copy

copy.o:copy.c
	@$(CC) $(CFALGS) -c copy.c
clean:
	@rm -rf $(obj) copy
