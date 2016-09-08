#include "../include/yapis_core.hpp"


const std::string YAPIsCore::MASERVICE_URL = "http://jlp.yahooapis.jp/MAService/V1/parse";
const std::string YAPIsCore::JIMSERVICE_URL = "http://jlp.yahooapis.jp/JIMService/V1/conversion";
const std::string YAPIsCore::FURIGANASERVICE_URL = "http://jlp.yahooapis.jp/FuriganaService/V1/furigana";
const std::string YAPIsCore::KOUSEISERVICE_URL = "http://jlp.yahooapis.jp/KouseiService/V1/kousei";
const std::string YAPIsCore::DASERVICE_URL = "http://jlp.yahooapis.jp/DAService/V1/parse";
const std::string YAPIsCore::KEYPHRASESERVICE_URL = "http://jlp.yahooapis.jp/KeyphraseService/V1/extract";

YAPIsCore::YAPIsCore(std::string APP_ID) : APP_ID(APP_ID)
{
}

const std::string YAPIsCore::get_maservice_url() const
{
    return this->MASERVICE_URL;
}

std::string YAPIsCore::get_appid() const
{
    return this->APP_ID;
}
