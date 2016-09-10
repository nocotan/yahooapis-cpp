#ifndef YAPIS_CPP_HPP
#define YAPIS_CPP_HPP

#include "./yapis_core.hpp"


class YAPIsCpp : public YAPIsCore
{
    private:
    public:
        YAPIsCpp(std::string);

        // libcurlのコールバック関数
        static size_t callbackWrite(char*, size_t, size_t, std::string*);

        // libcurlセットアップ関数
        std::string common_curl_setup(CURL*, std::string, int) const;

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

        // かな漢字変換の結果
        struct JIMResult {
            std::vector<std::string> segment_list;
            std::map<std::string, std::vector<std::string> > candidate_list;
        };

        // ルビ振りの結果
        struct FuriganaResult {
            std::vector<std::string> word_list;
            std::vector<std::string> subword_list;
            std::map<std::string, std::string> furigana_list;
            std::map<std::string, std::string> roman_list;
        };

        MAResult ma_post(std::string) const;
        JIMResult jim_post(std::string) const;
        FuriganaResult furigana_post(std::string) const;
};

#endif
