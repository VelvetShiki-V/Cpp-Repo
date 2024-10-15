#ifndef COMPILE_ONLINE
#include "header.cc"
#endif

void test1() {
    bool flag = Solution().isPalindrome(121);
    if(flag) {
        std::cout << "num: 121 judge success" << std::endl;
    }
    else {
        std::cout << "num: 121 judge failed" << std::endl;
    }
}

void test2() {
    bool flag = Solution().isPalindrome(2233);
    if(!flag) {
        std::cout << "num: 2233 judge success" << std::endl;
    }
    else {
        std::cout << "num: 2233 judge failed" << std::endl;
    }
}

void test3() {
    bool flag = Solution().isPalindrome(192939291);
    if(flag) {
        std::cout << "num: 192939291 judge success" << std::endl;
    }
    else {
        std::cout << "num: 192939291 judge failed" << std::endl;
    }
}

int main() {
    test1();
    test2();
    test3();
    return 0;
}