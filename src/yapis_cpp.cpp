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

YAPIsCpp::MAResult YAPIsCpp::ma_post(std::string sentence) const
{
    using namespace tinyxml2;

    CURL *curl;
    CURLcode res;
    std::string chunk;
    YAPIsCpp::MAResult result;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if (curl) {
        std::string url = YAPIsCore::get_maservice_url();
        std::string post_data = "appid="
            + YAPIsCore::get_appid()
            + "&results=ma&sentence="
            + sentence;

        // libcurlセットアップ
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

    // xmlパース処理
    XMLDocument doc;
    doc.Parse((const char*)chunk.c_str());

    XMLElement* ResultSet = doc.FirstChildElement("ResultSet");
    XMLElement* ma_result = ResultSet->FirstChildElement("ma_result");
    XMLElement* total_count = ma_result->FirstChildElement("total_count");
    XMLElement* filtered_count = ma_result->FirstChildElement("filtered_count");
    XMLElement* word_list = ma_result->FirstChildElement("word_list");

    for (XMLElement* el=word_list->FirstChildElement("word");
            el!=NULL; el=el->NextSiblingElement("word")) {
        XMLElement* surface = el->FirstChildElement("surface");
        XMLElement* reading = el->FirstChildElement("reading");
        XMLElement* pos = el->FirstChildElement("pos");

        result.word_list.push_back(surface->GetText());
        result.reading.insert(std::make_pair(surface->GetText(), reading->GetText()));
        result.pos.insert(std::make_pair(surface->GetText(), pos->GetText()));
    }

    result.total_count = std::stoi(total_count->GetText());
    result.filtered_count = std::stoi(filtered_count->GetText());

    return result;
}
