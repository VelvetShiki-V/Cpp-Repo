#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

void myperror(const char* message) {
    fprintf(stderr, "%s: %s\n", message, strerror(errno));
}

int main() {
    int fd = open("output.txt", O_RDONLY);
    if(fd < 0) {
        myperror("output open");
        return -1;
    }
    return 0;
}
