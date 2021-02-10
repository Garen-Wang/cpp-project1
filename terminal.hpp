#pragma once

#include <utility>
#include <vector>
#include <string>

enum class TextAttribute {
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
    White = 37,
    Default = 38
    // 38 is undefined, so default
};

enum class Background {
    Black = 40,
    Red = 41,
    Green = 42,
    Yellow = 43,
    Blue = 44,
    Magenta = 45,
    Cyan = 46,
    White = 47,
    Default = 48
    // 48 is undefined, so default
};

struct Style {
    TextAttribute text_attribute;
    Foreground foreground;
    Background background;
    bool operator == (const Style &rhs) const;
};
// white on black, no text attribute
Style default_style = {
    TextAttribute::Default, Foreground::Default, Background::Default
};

std::pair<unsigned int, unsigned int> get_terminal_size();

char sys_buf[10000];
// buffer, displayed after a flush
// if null, convert to space
std::string buffer;
// buffer style
// if null, convert to default_style
std::vector<Style> buffer_style;
std::vector<int> buffer_z;// 0 for space, must strictly greater to overlap
unsigned int screen_height, screen_width;

inline int getIndex(int x, int y);

class Terminal {
    private:
        // height and width of abstracted terminal area
        unsigned int height, width;
        // nullptr if actual terminal else sub-terminal
        Terminal *parent;
        // relative to the actual terminal (no need to care when passing parameters)
        // x_max = height - 1, y_max = width - 1
        unsigned int offset_x, offset_y;
    public:
        // constructor
        Terminal();
        Terminal(Terminal *parent, unsigned int height, unsigned int width, unsigned int offset_x, unsigned int offset_y);

        inline unsigned int getHeight();
        inline unsigned int getWidth();
        bool isActual();

        // print
        bool print(std::vector<std::string> image, int x, int y, Style style, int z_index);
};

// flush
void flush();
// clean
void clear();
void clearPart(int x, int y, int xx, int yy);