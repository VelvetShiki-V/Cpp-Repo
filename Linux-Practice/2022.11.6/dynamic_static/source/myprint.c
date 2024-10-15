#include"myprint.h"

void print2z(char c) {
    assert(c >= 'a' && c <= 'z');
    for(c; c <= 'z'; c++) {
        printf("%c ", c);
    }
}
