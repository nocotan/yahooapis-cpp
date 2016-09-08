#ifndef YAPIS_CPP_HPP
#define YAPIS_CPP_HPP

#include "yapis_core.hpp"


class YAPIsCpp : public YAPIsCore
{
    private:
    public:
        YAPIsCpp(std::string);

        // libcurlのコールバック関数
        static size_t callbackWrite(char*, size_t, size_t, std::string*);

        // 形態素解析の結果
        struct MAResult {
            int total_count;
            int filtered_count;
            std::vector<std::string> word_list;
            std::map<std::string, std::string> reading;
            std::map<std::string, std::string> pos;
            std::map<std::string, std::string> baseform;
            std::map<std::string, std::string> feature;
        };

        MAResult ma_post(std::string) const;
};

#endif
