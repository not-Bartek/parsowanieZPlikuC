#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    const char *path = "/tmp/moje_fifo";
    char buf[100];

    int fd = open(path, O_RDONLY); // Tu program stanie i będzie czekał na pisarza!
    read(fd, buf, sizeof(buf));
    printf("Odebrano: %s\n", buf);
    
    close(fd);
    return 0;
}