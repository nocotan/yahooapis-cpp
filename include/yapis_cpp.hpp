#ifndef YAPIS_CPP_HPP
#define YAPIS_CPP_HPP

#include "./yapis_core.hpp"


class YAPIsCpp : public YAPIsCore
{
    private:
    public:
        YAPIsCpp(std::string);
        static size_t callbackWrite(char*, size_t, size_t, std::string*);
        std::string ma_result(std::string) const;
};

#endif
