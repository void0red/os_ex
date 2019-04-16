#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
static void usage(char*);
int main(int argc, char* argv[])
{
    char buf[1024];
    if(argc != 3) {
        usage(argv[0]);
        return 0;
    }
    int src = open(argv[1], O_RDONLY);
    if(src < 0) {
        fprintf(stderr, "Error: cant open source file.\n");
        return 0;
    }
    int dest = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(dest < 0) {
        fprintf(stderr, "Error: cant open dest file.\n");
        return 0;
    }
    int pos = 0;
    while((pos = read(src, buf, 1024)) > 0)
    {
        write(dest, buf, pos);
    }
    close(src);
    close(dest);
    return 0;
}

static void usage(char *name)
{
    fprintf(stderr, "Usage: %s source [dest]\n", name);
}
