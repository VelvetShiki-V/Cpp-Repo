#include<stdio.h>
#include<unistd.h>

int main() {
    printf("start\n");

    execl("/usr/bin/ls", "ls", "-l" ,"--color=auto", NULL);

    printf("end\n");
}
