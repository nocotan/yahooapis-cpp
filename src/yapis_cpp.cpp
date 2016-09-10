#include "../include/yapis_cpp.hpp"

using namespace std;
using namespace tinyxml2;
#define XML_FOR(x,a,b) for(auto&& (x)=YAPIsCpp::get_element((a),(b));(x)!=NULL;(x)=YAPIsCpp::get_next((x),(b)))

YAPIsCpp::YAPIsCpp(string APP_ID) : YAPIsCore(APP_ID)
{
}

size_t YAPIsCpp::callbackWrite(char *ptr, size_t size, size_t nmemb, string *stream)
{
    int data_length = size * nmemb;
    stream->append(ptr, data_length);
    return data_length;
}

string YAPIsCpp::common_curl_setup(CURL *curl, string sentence, int type) const
{
    string url;
    string post_data;
    string chunk;
    CURLcode res;

    /**
     * type:
     * 0 => 形態素解析
     * 1 => ひらがな漢字変換
     * 2 => ルビ振り
     * 3 => 校正支援
     */
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
    else if (type==2) {
        url = YAPIsCore::get_furiganaservice_url();
        post_data = "appid="
            + YAPIsCore::get_appid()
            + "&grade=1"
            + "&sentence="
            + sentence;
    }
    else if (type==3) {
        url = YAPIsCore::get_kouseiservice_url();
        post_data = "appid="
            + YAPIsCore::get_appid()
            + "&sentence="
            + sentence;
    }

    // curlセットアップ
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, (const char*)url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, (const char*)post_data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackWrite);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            cerr << "curl_easy_perform() failed" << endl;

        curl_easy_cleanup(curl);
    }

    return chunk;
}

XMLElement* YAPIsCpp::get_element(XMLElement* current, string el) const
{
    return current->FirstChildElement((const char*)el.c_str());
}

XMLElement* YAPIsCpp::get_next(XMLElement* current, string el) const
{
    return current->NextSiblingElement((const char*)el.c_str());
}
/**
 * 形態素解析結果
 * @param std::string
 */
YAPIsCpp::MAResult YAPIsCpp::ma_post(string sentence) const
{
    CURL *curl;
    MAResult result;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    string chunk = common_curl_setup(curl, sentence, 0);

    curl_global_cleanup();

    // xmlパース処理
    XMLDocument doc;
    doc.Parse((const char*)chunk.c_str());

    auto&& ResultSet = doc.FirstChildElement("ResultSet");
    auto&& ma_result = get_element(ResultSet, "ma_result");
    auto&& total_count = get_element(ma_result, "total_count");
    auto&& filtered_count = get_element(ma_result, "filtered_count");
    auto&& word_list = get_element(ma_result, "word_list");

    XML_FOR(word, word_list, "word") {
        auto&& surface = get_element(word, "surface");
        auto&& reading = get_element(word, "reading");
        auto&& pos = get_element(word, "pos");
        auto&& baseform = get_element(word, "baseform");
        auto&& feature = get_element(word, "feature");

        result.word_list.push_back(surface->GetText());
        result.reading.insert(make_pair(surface->GetText(), reading->GetText()));
        result.pos.insert(make_pair(surface->GetText(), pos->GetText()));

        if (baseform != NULL)
            result.baseform.insert(make_pair(surface->GetText(), baseform->GetText()));
        if (feature != NULL)
            result.feature.insert(make_pair(surface->GetText(), feature->GetText()));
    }

    result.total_count = stoi(total_count->GetText());
    result.filtered_count = stoi(filtered_count->GetText());

    return result;
}

/**
 * かな漢字変換結果
 * @param std::string
 */
YAPIsCpp::JIMResult YAPIsCpp::jim_post(string sentence) const
{
    CURL *curl;
    JIMResult result;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    string chunk = common_curl_setup(curl, sentence, 1);

    curl_global_cleanup();

    // xmlパース処理
    XMLDocument doc;
    doc.Parse((const char*)chunk.c_str());

    auto&& ResultSet = doc.FirstChildElement("ResultSet");
    auto&& Result = get_element(ResultSet, "Result");
    auto&& SegmentList = get_element(Result, "SegmentList");

    XML_FOR(Segment, SegmentList, "Segment") {
        auto&& SegmentText = get_element(Segment, "SegmentText");
        result.segment_list.push_back(SegmentText->GetText());

        auto&& CandidateList = get_element(Segment, "CandidateList");
        vector<string> candidate_list;
        for (auto&& Candidate=get_element(CandidateList, "Candidate");
                Candidate!=NULL; Candidate=get_next(Candidate, "Candidate")) {

            candidate_list.push_back(Candidate->GetText());
        }
        result.candidate_list.insert(make_pair(SegmentText->GetText(), candidate_list));
    }

    return result;
}

/**
 * ルビ振り結果
 * @param std::string
 */
YAPIsCpp::FuriganaResult YAPIsCpp::furigana_post(string sentence) const
{

    CURL *curl;
    FuriganaResult result;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    string chunk = common_curl_setup(curl, sentence, 2);

    curl_global_cleanup();

    // xmlパース処理
    XMLDocument doc;
    doc.Parse((const char*)chunk.c_str());

    auto&& ResultSet = doc.FirstChildElement("ResultSet");
    auto&& Result = get_element(ResultSet, "Result");
    auto&& WordList = get_element(Result, "WordList");

    XML_FOR(Word, WordList, "Word") {
        auto&& Surface = get_element(Word, "Surface");
        result.word_list.push_back(Surface->GetText());

        auto&& Furigana = get_element(Word, "Furigana");
        if (Furigana!=NULL)
            result.furigana_list.insert(make_pair(Surface->GetText(), Furigana->GetText()));

        auto&& Roman = get_element(Word, "Roman");
        if (Roman!=NULL)
            result.roman_list.insert(make_pair(Surface->GetText(), Roman->GetText()));

        auto&& SubWordList = get_element(Word, "SubWordList");
        if (SubWordList!=NULL) {
            XML_FOR(SubWord, SubWordList, "SubWord") {
                auto&& Surface = get_element(SubWord, "Surface");
                result.subword_list.push_back(Surface->GetText());

                auto&& Furigana = get_element(SubWord, "Furigana");
                if (Furigana!=NULL)
                    result.furigana_list.insert(make_pair(Surface->GetText(), Furigana->GetText()));

                auto&& Roman = get_element(SubWord, "Roman");
                if (Roman!=NULL)
                    result.roman_list.insert(make_pair(Surface->GetText(), Roman->GetText()));
            }
        }
    }

    return result;
}

/**
 * 校正支援結果
 * @param std::string
 */
YAPIsCpp::KouseiResult YAPIsCpp::kousei_post(string sentence) const
{
    CURL *curl;
    KouseiResult result;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    string chunk = common_curl_setup(curl, sentence, 3);

    curl_global_cleanup();

    // xmlパース処理
    XMLDocument doc;
    doc.Parse((const char*)chunk.c_str());

    auto&& ResultSet = doc.FirstChildElement("ResultSet");
    XML_FOR(Result, ResultSet, "Result") {
        auto&& StartPos = get_element(Result, "StartPos");
        result.start_pos.push_back(stoi(StartPos->GetText()));

        auto&& Length = get_element(Result, "Length");
        result.length.insert(make_pair(stoi(StartPos->GetText()), stoi(Length->GetText())));

        auto&& Surface = get_element(Result, "Surface");
        result.surface.insert(make_pair(stoi(StartPos->GetText()), Surface->GetText()));

        auto&& ShitekiWord = get_element(Result, "ShitekiWord");
        result.shiteki_word.insert(make_pair(stoi(StartPos->GetText()), ShitekiWord->GetText()));

        auto&& ShitekiInfo = get_element(Result, "ShitekiInfo");
        result.shiteki_info.insert(make_pair(stoi(StartPos->GetText()), ShitekiInfo->GetText()));
    }

    return result;
}
