#include "./include/yapis_cpp.hpp"
#include <iostream>

int main() {
    YAPIsCpp yapis = YAPIsCpp("dj0zaiZpPURWbUpWY1RmbnU3NyZzPWNvbnN1bWVyc2VjcmV0Jng9ZDg-");
    YAPIsCpp::MAResult res = yapis.ma_post("庭には二羽鶏がいる庭");
    std::cout << res.total_count << std::endl;
    std::cout << res.filtered_count << std::endl;
    for (std::string s : res.word_list) {
        std::cout << s << std::endl;
        std::cout << res.reading[s] << std::endl;
        std::cout << res.pos[s] << std::endl;
        std::cout << res.baseform[s] << std::endl;
        std::cout << res.feature[s] << std::endl;
    }

    YAPIsCpp::JIMResult res2 = yapis.jim_post("おなかがすいた");
    for (std::string s : res2.segment_list) {
        std::cout << s << std::endl;
        std::vector<std::string> candidate_list = res2.candidate_list[s];
        for (auto el : candidate_list) {
            std::cout << el << std::endl;
        }
    }

    YAPIsCpp::FuriganaResult res3 = yapis.furigana_post("今日は日曜日");
    for (auto s : res3.word_list) {
        std::cout << s << std::endl;
        std::cout << res3.furigana_list[s] << std::endl;
        std::cout << res3.roman_list[s] << std::endl;
    }

    YAPIsCpp::KouseiResult res4 = yapis.kousei_post("遙か彼方に小形飛行機が見える");
    for (auto s : res4.start_pos) {
        std::cout << s << std::endl;
        std::cout << res4.length[s] << std::endl;
        std::cout << res4.surface[s] << std::endl;
        std::cout << res4.shiteki_word[s] << std::endl;
        std::cout << res4.shiteki_info[s] << std::endl;
    }
    return 0;
}
