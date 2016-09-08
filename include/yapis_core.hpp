#ifndef YAPIS_CORE_HPP
#define YAPIS_CORE_HPP

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <curl/curl.h>

#include "tinyxml2.h"


class YAPIsCore
{
    private:
        // 形態素解析API
        static const std::string MASERVICE_URL;
        // かな漢字変換API
        static const std::string JIMSERVICE_URL;
        // ルビ振りAPI
        static const std::string FURIGANASERVICE_URL;
        // 校正支援API
        static const std::string KOUSEISERVICE_URL;
        // 日本語係り受け解析API
        static const std::string DASERVICE_URL;
        // キーフレーズ抽出API
        static const std::string KEYPHRASESERVICE_URL;

        // YahooアプリケーションID
        std::string APP_ID;
    public:
        YAPIsCore(std::string);
        const std::string get_maservice_url() const;
        const std::string get_jimservice_url() const;
        const std::string get_furiganaservice_url() const;
        const std::string get_kouseiservice_url() const;
        const std::string get_daservice_url() const;
        const std::string get_keyphraseservice_url() const;
        std::string get_appid() const;
};

#endif
