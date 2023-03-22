#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define SHM_SIZE 1024

int main()
{
    int fd;
    void *ptr;
    char *msg = "Hello, shared memory!";

    // Create a new shared memory object
    fd = shm_open("/my_shm", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        fprintf(stderr, "Error creating shared memory object: %s\n", strerror(errno));
        return 1;
    }
}