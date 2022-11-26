#pragma once

#include <cstdlib>
#include <string>

class Font {
public:
    static constexpr std::size_t WIDTH{12};
    static constexpr std::size_t HEIGHT{17};

    static std::size_t widthOf(const std::string &);
};
