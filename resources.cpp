#pragma once

#include <vector>
#include <string>

// restrict that size must be a square
namespace images {
    std::vector<std::string> letter_x = {
        R"(__  __)",
        R"(\ \/ /)",
        R"( >  < )",
        R"(/_/\_\)",
    };
    std::vector<std::string> letter_k = {
        R"( _    )",
        R"(| | __)",
        R"(| |/ /)",
        R"(|   < )",
        R"(|_|\_\)",
    };
    std::vector<std::string> letter_c = {
        R"(  ___ )",
        R"( / __|)",
        R"(| (__ )",
        R"( \___|)",
    };
    std::vector<std::string> letter_d = {
        R"(     _ )",
        R"(  __| |)",
        R"( / _` |)",
        R"(| (_| |)",
        R"( \__,_|)",
    };
    std::vector<std::string> number_505 = {
        R"( ____      ___     ____  )",
        R"(| ___|    / _ \   | ___| )",
        R"(|___ \   | | |    |___ \ )",
        R"( ___)    | |_|    |___) |)",
        R"(|____/    \___/   |____/ )",
    };
};

unsigned int get_image_height(std::vector<std::string> x) {
    return x.size();
}
unsigned int get_image_width(std::vector<std::string> x) {
    return x[0].length();
}