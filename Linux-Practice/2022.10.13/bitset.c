#include<stdio.h>

#define ONE 0x01
#define TWO 0x02
#define THREE 0x04

void print(int flags) {
    if(flags & ONE) printf("ONE\n");
    if(flags & TWO) printf("TWO\n");
    if(flags & THREE) printf("THREE\n");
}

int main() {
    print(ONE);
    printf("-----------------------------\n");
    print(TWO);
    printf("-----------------------------\n");
    print(ONE | TWO | THREE);
    printf("-----------------------------\n");
    print(ONE | THREE);
    return 0;
}
