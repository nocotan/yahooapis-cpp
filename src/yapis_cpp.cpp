#include "../include/yapis_cpp.hpp"

YAPIsCpp::YAPIsCpp(std::string APP_ID) : YAPIsCore(APP_ID)
{
}

std::string YAPIsCpp::ma_result(std::string sentence) const
{
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    std::string chunk;


    curl_easy_setopt(curl, CURLOPT_URL, &YAPIsCore::get_maservice_url);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return chunk;
}
