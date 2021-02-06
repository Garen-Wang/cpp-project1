#pragma once

#include <utility>

enum TextAttribute {
    Default = 0,
    Bold = 1,
    Underscore = 4,
    Blink = 5
};

enum class Foreground {
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37
};

enum class Background {
    Black = 40,
    Red = 41,
    Green = 42,
    Yellow = 43,
    Blue = 44,
    Magenta = 45,
    Cyan = 46,
    White = 47
};

std::pair<unsigned int, unsigned int> get_terminal_size();

class Terminal {
    private:
        unsigned int width;
        unsigned int height;
        // nullptr if actual terminal else sub-terminal
        Terminal *parent;
        unsigned int offset_width;
        unsigned int offset_height;
    public:
        // constructor and destructor
        Terminal();
        Terminal(Terminal *parent, unsigned int width, unsigned int height, unsigned int offset_width, unsigned int offset_height);
        ~Terminal();

        // debug
        unsigned int getWidth();
        unsigned int getHeight();
        bool isActual();

        // print
        void print();
        // clean
        void clear();
};

