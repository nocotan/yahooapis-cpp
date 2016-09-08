#ifndef YAPIS_CPP_HPP
#define YAPIS_CPP_HPP

#include "./yapis_core.hpp"


class YAPIsCpp : public YAPIsCore
{
    public:
        YAPIsCpp(std::string);
        std::string ma_result(std::string) const;
};

#endif
