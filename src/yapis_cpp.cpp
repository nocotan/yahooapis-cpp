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

std::string YAPIsCpp::common_curl_setup(CURL *curl, std::string sentence, int type) const
{
    std::string url;
    std::string post_data;
    std::string chunk;
    CURLcode res;
    if (type==0) {
        url = YAPIsCore::get_maservice_url();
        post_data = "appid="
            + YAPIsCore::get_appid()
            + "&results=ma&response=surface,reading,pos,baseform,feature&sentence="
            + sentence;
    }
    else if (type==1) {
        url = YAPIsCore::get_jimservice_url();
        post_data = "appid="
            + YAPIsCore::get_appid()
            + "&sentence="
            + sentence;
    }
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, (char*)url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, (char*)post_data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackWrite);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed" << std::endl;

        curl_easy_cleanup(curl);
    }

    return chunk;
}

YAPIsCpp::MAResult YAPIsCpp::ma_post(std::string sentence) const
{
    using namespace tinyxml2;

    CURL *curl;
    YAPIsCpp::MAResult result;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    std::string chunk = this->common_curl_setup(curl, sentence, 0);

    curl_global_cleanup();

    // xmlパース処理
    XMLDocument doc;
    doc.Parse((const char*)chunk.c_str());

    auto ResultSet = doc.FirstChildElement("ResultSet");
    auto ma_result = ResultSet->FirstChildElement("ma_result");
    auto total_count = ma_result->FirstChildElement("total_count");
    auto filtered_count = ma_result->FirstChildElement("filtered_count");
    auto word_list = ma_result->FirstChildElement("word_list");

    for (auto el=word_list->FirstChildElement("word");
            el!=NULL; el=el->NextSiblingElement("word")) {
        auto surface = el->FirstChildElement("surface");
        auto reading = el->FirstChildElement("reading");
        auto pos = el->FirstChildElement("pos");
        auto baseform = el->FirstChildElement("baseform");
        auto feature = el->FirstChildElement("feature");

        result.word_list.push_back(surface->GetText());
        result.reading.insert(std::make_pair(surface->GetText(), reading->GetText()));
        result.pos.insert(std::make_pair(surface->GetText(), pos->GetText()));

        if (baseform != NULL)
            result.baseform.insert(std::make_pair(surface->GetText(), baseform->GetText()));
        if (feature != NULL)
            result.feature.insert(std::make_pair(surface->GetText(), feature->GetText()));
    }

    result.total_count = std::stoi(total_count->GetText());
    result.filtered_count = std::stoi(filtered_count->GetText());

    return result;
}

YAPIsCpp::JIMResult YAPIsCpp::jim_post(std::string sentence) const
{
    using namespace tinyxml2;

    CURL *curl;
    YAPIsCpp::JIMResult result;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    std::string chunk = this->common_curl_setup(curl, sentence, 1);

    curl_global_cleanup();

    // xmlパース処理
    XMLDocument doc;
    doc.Parse((const char*)chunk.c_str());

    auto ResultSet = doc.FirstChildElement("ResultSet");
    auto Result = ResultSet->FirstChildElement("Result");
    auto SegmentList = Result->FirstChildElement("SegmentList");


    for (auto el=SegmentList->FirstChildElement("Segment");
            el!=NULL; el=el->NextSiblingElement("Segment")) {
        auto SegmentText = el->FirstChildElement("SegmentText");
        result.segment_list.push_back(SegmentText->GetText());

        auto CandidateList = el->FirstChildElement("CandidateList");
        std::vector<std::string> candidate_list;
        for (auto Candidate=CandidateList->FirstChildElement("Candidate");
                Candidate!=NULL; Candidate=Candidate->NextSiblingElement("Candidate")) {
            candidate_list.push_back(Candidate->GetText());
        }
        result.candidate_list.insert(std::make_pair(SegmentText->GetText(), candidate_list));
    }

    return result;
}
