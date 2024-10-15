#ifndef COMPILE_ONLINE
#include "header.cc"
#endif

void test1(const std::vector<int> v) {
    bool flag = Solution().getMax(v);
    if(flag) {
        std::cout << "num: 121 judge success" << std::endl;
    }
    else {
        std::cout << "num: 121 judge failed" << std::endl;
    }
}

void test2(const std::vector<int> v) {
    bool flag = Solution().getMax(v);
    if(!flag) {
        std::cout << "num: 2233 judge success" << std::endl;
    }
    else {
        std::cout << "num: 2233 judge failed" << std::endl;
    }
}


int main() {
    std::vector<int> v1{1,2,3,4,5,6,7,8,9};
    std::vector<int> v2{6,4,2,9,5,3,4,6,18};
    test1(v1);
    test2(v2);
    return 0;
}