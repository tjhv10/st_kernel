#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEVICE_FILE "/dev/st_kernel"
#define BUFFER_SIZE 1024

int main() {
    int fd;
    char buffer[BUFFER_SIZE];

    // Open the device file for writing
    fd = open(DEVICE_FILE, O_WRONLY);
    if (fd == -1) {
        perror("Failed to open the device files");
        return -1;
    }

    // Get the input from the user
    printf("Enter the text to encrypt: ");
    fgets(buffer, BUFFER_SIZE, stdin);

    // Write the input to the device file
    ssize_t bytes_written = write(fd, buffer, strlen(buffer));
    if (bytes_written == -1) {
        perror("Failed to write to the device file");
        close(fd);
        return -1;
    }

    // Close the device file
    close(fd);

    printf("Text sent to the device file.\n");
    return 0;
}
