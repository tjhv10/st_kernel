#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char message[] = "Hello, XOR!";
    ssize_t bytes_written;

    fd = open("/dev/st_kernel", O_WRONLY);
    if (fd == -1) {
        perror("Failed to open the device file");
        return EXIT_FAILURE;
    }

    bytes_written = write(fd, message, sizeof(message));
    if (bytes_written == -1) {
        perror("Failed to write to the device file");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Message successfully written to the device file\n");

    close(fd);

    return EXIT_SUCCESS;
}
