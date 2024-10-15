#include<stdio.h>
#include<string.h>
#include<unistd.h>
#define MAX 102
int main()
{
    char status[] = "|/-\\";
    char bar[MAX];
    memset(bar,0,MAX - 1);
    int i=0;
    for(i = 0; i <= 100; i++)
    {
        printf("[%-100s][%d%%] %c\r",bar,i,status[i%4]);
        bar[i]='#';
        fflush(stdout);
        usleep(30000);
    }
    printf("\n");
    return 0;
}
