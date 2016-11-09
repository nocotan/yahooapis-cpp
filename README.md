# yahooapis-cpp
[![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE)  
C/C++ Yahoo API Wrapper

##Usage

###Yahoo形態素解析

```c++
#include "yapis_cpp.hpp"

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

###Yahooかな漢字変換

```c++
#include "yapis_cpp.hpp"

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

###ルビ振り

```c++
#include "yapis_cpp.hpp"

int main() {
    YAPIsCpp yapis = YAPIsCpp("<Your APP ID>");
    YAPIsCpp::FuriganaResult res = yapis.furigana_post("今日は日曜日");
        for (auto s : res.word_list) {
             std::cout << s << std::endl;
             std::cout << res.furigana_list[s] << std::endl;
             std::cout << res.roman_list[s] << std::endl;
        }
    }
}
```

###校正支援

```c++
#include "yapis_cpp.hpp"

int main() {
    YAPIsCpp::KouseiResult res = yapis.kousei_post("遙か彼方に小形飛行機が見える");
    for (auto s : res.start_pos) {
        std::cout << s << std::endl;
        std::cout << res.length[s] << std::endl;
        std::cout << res.surface[s] << std::endl;
        std::cout << res.shiteki_word[s] << std::endl;
        std::cout << res.shiteki_info[s] << std::endl;
    }
    return 0;
}
```
