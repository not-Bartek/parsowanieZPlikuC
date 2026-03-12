#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *path = "/tmp/moje_fifo";
    mkfifo(path, 0666); // Tworzymy FIFO (jeśli nie istnieje)

    int fd = open(path, O_WRONLY); // Tu program stanie i będzie czekał na czytelnika!
    write(fd, "Cześć z innego procesu!", 24);
    close(fd);
    return 0;
}