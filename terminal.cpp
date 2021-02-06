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


// constructor of actual terminal
Terminal::Terminal():
offset_x(0), offset_y(0) {
    this->parent = nullptr;
    auto temp = get_terminal_size();
    this->width = temp.first;
    this->height = temp.second;
    this->buffer.resize(this->width * this->height);
    this->buffer_style.resize(this->width * this->height);
    screen.resize(this->width * this->height);
    screen_style.resize(this->width * this->height);
    screen_height = this->height;
    screen_width = this->width;
}

// constructor of subterminal
Terminal::Terminal(Terminal *parent, unsigned int height, unsigned int width, unsigned int offset_x, unsigned int offset_y):
parent(parent), height(height), width(width) {
    this->offset_x = parent->offset_x + offset_x;
    this->offset_y = parent->offset_y + offset_y;
    this->buffer.resize(this->width * this->height);
    this->buffer_style.resize(this->width * this->height);
}

// destructor
Terminal::~Terminal() {
    // really free memory rather than clear()
    std::vector<char>().swap(this->buffer);
    std::vector<Point>().swap(this->buffer_style);
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

unsigned int Terminal::getIndex(unsigned int x, unsigned int y) {
    return x * this->width + y;
}

void Terminal::print(std::vector<std::string> image, unsigned int x, unsigned int y, Point style) {
    int image_height = image.size(), image_width = image[0].length();
    for(int i = x; i >= 0 && i + image_height <= this->height; ++i) {
        for(int j = y; j >= 0 && j + image_width <= this->width; ++j) {
            int idx = getIndex(i, j);
            buffer[idx] = image[i][j];
            buffer_style[idx] = style;
        }
    }
}

void Terminal::loadScreen() {
    if(this->parent != nullptr) this->parent->loadScreen();
    assert(this->offset_x + this->height <= screen_height && this->offset_x >= 0);
    assert(this->offset_y + this->width <= screen_width && this->offset_y >= 0);

    for(int i = 0; i < this->height; ++i) {
        for(int j = 0; j < this->width; ++j) {
            unsigned int idx = getIndex(i, j);
            unsigned int screen_idx = getIndex(i + this->offset_x, j + this->offset_y);
            screen[screen_idx] = this->buffer[idx];
            screen_style[screen_idx] = this->buffer_style[idx];
        }
    }
}

void Terminal::flush() {

}

void Terminal::clear() {
    // std::vector<char>().swap(screen);
    // std::vector<Point>().swap(screen_style);
    // screen.resize(screen_height * screen_width);
    // screen_style.resize(screen_height * screen_width);
}