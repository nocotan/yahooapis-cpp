#include "./include/yapis_cpp.hpp"
#include <iostream>

int main() {
    YAPIsCpp yapis = YAPIsCpp("dj0zaiZpPURWbUpWY1RmbnU3NyZzPWNvbnN1bWVyc2VjcmV0Jng9ZDg-");
    std::string s = yapis.ma_result("test");
    std::cout << s << std::endl;
    return 0;
}
