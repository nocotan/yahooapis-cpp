# yahooapis-cpp
C/C++ Yahoo API Wrapper

##Usage

Yahoo形態素解析

```example.cpp
#include "yapis_cpp.hpp"
#include <iostream>

int main() {
    YAPIsCpp yapis = YAPIsCpp("<Your APP ID>");
    YAPIsCpp::MAResult res = yapis.ma_post("庭には二羽鶏がいる");
    std::cout << res.total_count << std::endl;
    std::cout << res.filtered_count << std::endl;
    for (std::string s : res.word_list) {
        std::cout << s << std::endl;
        std::cout << res.reading[s] << std::endl;
        std::cout << res.pos[s] << std::endl;
        std::cout << res.baseform[s] << std::endl;
        std::cout << res.feature[s] << std::endl;
    }
    return 0;
}
```

Yahooかな漢字変換

```
#include "yapis_cpp.hpp"`
#include <iostream>
#include <vector>

int main() {
    YAPIsCpp yapis = YAPIsCpp("<Your APP ID>");
    YAPIsCpp::JIMResult res = yapis.jim_post("おなかがすいた");
    for (auto s : res.segment_list) {
        std::cout << s << std::endl;

        for (auto el : res.candidate_list[s]) {
            std::cout << el <<std::endl;
        }
    }
}
```
