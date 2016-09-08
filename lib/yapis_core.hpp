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
        static const std::string MASERVICE_URL;
        static const std::string JIMSERVICE_URL;
        static const std::string FURIGANASERVICE_URL;
        static const std::string KOUSEISERVICE_URL;
        static const std::string DASERVICE_URL;
        static const std::string KEYPHRASESERVICE_URL;

        std::string APP_ID;
    public:
        YAPIsCore(std::string);
        const std::string get_maservice_url() const;
        std::string get_appid() const;
};

#endif
