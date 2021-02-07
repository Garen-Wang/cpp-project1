#pragma once

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <assert.h>

#include <vector>
#include <string>

#include "terminal.hpp"

// first: height, second: width
std::pair<unsigned int, unsigned int> get_terminal_size() {
    termios init_setting, new_setting;
    tcgetattr(STDOUT_FILENO, &init_setting);
    new_setting = init_setting;
    // ICANON: don't need to press enter to let scanf begin
    new_setting.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDOUT_FILENO, TCSAFLUSH, &new_setting);

    unsigned int original_width, original_height, width, height;
    printf("\033[6n");
    scanf("\033[%u;%uR", &original_height, &original_width);
    printf("\033[2077;2077H \033[6n");
    scanf("\033[%u;%uR", &height, &width);
    printf("\033[%u;%uH", original_height, original_width);

    // reset
    tcsetattr(STDOUT_FILENO, TCSAFLUSH, &init_setting);
    return std::make_pair(height, width);
}

bool Point::operator == (const Point &rhs) const {
    return text_attribute == rhs.text_attribute && foreground == rhs.foreground && background == rhs.background;
}

// constructor of actual terminal
Terminal::Terminal():
offset_x(0), offset_y(0) {
    this->parent = nullptr;
    auto temp = get_terminal_size();
    screen_height = this->height = temp.first;
    screen_width = this->width = temp.second;
    unsigned int size = this->height * this->width;
    buffer.resize(size);
    buffer_style.resize(size);
}

// constructor of subterminal
Terminal::Terminal(Terminal *parent, unsigned int height, unsigned int width, unsigned int offset_x, unsigned int offset_y):
parent(parent), height(height), width(width) {
    this->offset_x = parent->offset_x + offset_x;
    this->offset_y = parent->offset_y + offset_y;
}

inline unsigned int Terminal::getHeight() {
    return this->height;
}
inline unsigned int Terminal::getWidth() {
    return this->width;
}
bool Terminal::isActual() {
    return parent == nullptr;
}

unsigned int getIndex(unsigned int x, unsigned int y) {
    return x * screen_width + y;
}

void Terminal::print(std::vector<std::string> image, unsigned int x, unsigned int y, Point style, int z_index) {
    int image_height = image.size(), image_width = image[0].length();
    assert(x + image_height <= this->height && y + image_width <= this->width);
    assert(this->offset_x + this->height <= screen_height);
    assert(this->offset_y + this->width <= screen_width);
    for(int i = 0; i < image_height; ++i) {
        for(int j = 0; j < image_width; ++j) {
            unsigned int idx = getIndex(i + x + this->offset_x, j + y + this->offset_y);
            buffer[idx] = image[i][j];
            buffer_style[idx] = style;
        }
    }
}

void Terminal::flush() {
    assert(this->parent == nullptr);
    unsigned int size = screen_height * screen_width;
    for(int l = 0, r = 0; l < size; l = r) {
        while(r < size && buffer_style[r] == buffer_style[l]) {
            if(!buffer[r]) buffer[r] = ' ';
            ++r;
        }
        // printf("[%d, %d): %d %d %d\n", l, r, buffer_style[l].text_attribute, buffer_style[l].foreground, buffer_style[l].background);
        std::string temp = buffer.substr(l, r - l);
        printf("\033[%d;%d;%dm%s", buffer_style[l].text_attribute, buffer_style[l].foreground, buffer_style[l].background, temp.c_str());
    }
    fflush(0);
}

void Terminal::clear() {
    assert(this->parent == nullptr);
    unsigned int size = screen_height * screen_width;
    buffer = "";
    buffer.resize(size);
    std::vector<Point>().swap(buffer_style);
    buffer_style.resize(size);
}