#include "../include/yapis_cpp.hpp"

YAPIsCpp::YAPIsCpp(std::string APP_ID) : YAPIsCore(APP_ID)
{
}

size_t YAPIsCpp::callbackWrite(char *ptr, size_t size, size_t nmemb, std::string *stream)
{
    int data_length = size * nmemb;
    stream->append(ptr, data_length);
    return data_length;
}

std::string YAPIsCpp::ma_result(std::string sentence) const
{
    CURL *curl;
    CURLcode res;
    std::string chunk;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if (curl) {
        std::string url = YAPIsCore::get_maservice_url();
        std::string post_data = "appid=" + YAPIsCore::get_appid() + "&results=ma&sentence=hello";
        curl_easy_setopt(curl, CURLOPT_URL, (char*)url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, (char*)post_data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackWrite);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed" << std::endl;
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return chunk;
}
