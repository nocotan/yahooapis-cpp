#include "./include/yapis_cpp.hpp"
#include <iostream>

int main() {
    YAPIsCpp yapis = YAPIsCpp("0000");
    std::string s = yapis.ma_result("test");
    std::cout << s << std::endl;
    return 0;
}
