#ifndef YAPIS_CORE_HPP
#define YAPIS_CORE_HPP

#include <string>


class YAPIsCore
{
    private:
        constexpr std::string MASERVICE_URL = "http://jlp.yahooapis.jp/MAService/V1/parse";
        constexpr std::string JIMSERVICE_URL = "http://jlp.yahooapis.jp/JIMService/V1/conversion";
        constexpr std::string FURIGANASERVICE_URL = "http://jlp.yahooapis.jp/FuriganaService/V1/furigana";
        constexpr std::string KOUSEISERVICE_URL = "http://jlp.yahooapis.jp/KouseiService/V1/kousei";
        constexpr std::string DASERVICE_URL = "http://jlp.yahooapis.jp/DAService/V1/parse";
        constexpr std::string KEYPHRASESERVICE_URL = "http://jlp.yahooapis.jp/KeyphraseService/V1/extract";

        std::string APP_ID;
    public:
        YAPIsCore(std::string);
};

#endif
