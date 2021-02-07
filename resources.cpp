#pragma once

#include <vector>
#include <string>

// restrict that size must be a square
namespace images {
    std::vector<std::string> x = {
        R"(__  __)",
        R"(\ \/ /)",
        R"( >  < )",
        R"(/_/\_\)",
    };
    std::vector<std::string> k = {
        R"( _    )",
        R"(| | __)",
        R"(| |/ /)",
        R"(|   < )",
        R"(|_|\_\)",
    };
    std::vector<std::string> c = {
        R"(  ___ )",
        R"( / __|)",
        R"(| (__ )",
        R"( \___|)",
    };
    std::vector<std::string> d = {
        R"(     _ )",
        R"(  __| |)",
        R"( / _` |)",
        R"(| (_| |)",
        R"( \__,_|)",
    };
};

unsigned int get_image_height(std::vector<std::string> x) {
    return x.size();
}
unsigned int get_image_width(std::vector<std::string> x) {
    return x[0].length();
}