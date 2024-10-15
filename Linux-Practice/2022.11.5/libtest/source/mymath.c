#include"mymath.h"

int multi(int begin, int end) {
    int ret = 1;
    for(begin; begin != end; begin++) {
        ret *= begin;
    }
    return ret;
}
