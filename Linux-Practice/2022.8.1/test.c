#include<stdio.h>
int add(int x)
{
    for(int i = 0; i <= 100; i++)
    {
        x += i;
    }
    return x;
}

int main()
{
    printf("Hello git, this is linux calling!\n");
    int num = 0;
    num = add(num);
    printf("add result = %d\n", num);
    printf("space1\n");
    printf("space2\n");
    printf("space3\n");
    printf("space4\n");
    printf("space5\n");
    printf("space6\n");
    printf("space7\n");
    return 0;
}
