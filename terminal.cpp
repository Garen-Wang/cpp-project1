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

bool Style::operator == (const Style &rhs) const {
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
    buffer_z.resize(size);
    flush();
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

inline int getIndex(int x, int y) {
    return x * screen_width + y;
}

bool Terminal::print(std::vector<std::string> image, int x, int y, Style style, int z_index) {
    int image_height = image.size(), image_width = image[0].length();
    // x coordinate: [x + offset_x, x + offset_x + image_height)
    // y coordinate: [y + offset_y, y + offset_y + image_width)
    bool flag = (x + offset_x + image_height > 0 || x + offset_x < screen_height) && (y + offset_y + image_width > 0 || y + offset_y < screen_width);
    if(!flag) return false;
    // assert(x + image_height <= this->height && y + image_width <= this->width);
    // assert(this->offset_x + this->height <= screen_height);
    // assert(this->offset_y + this->width <= screen_width);
    for(int i = 0; i < image_height; ++i) {
        int x_new = i + x + offset_x;
        if(x_new < 0 || x_new >= screen_height) continue;
        for(int j = 0; j < image_width; ++j) {
            int y_new = j + y + offset_y;
            if(0 <= y_new && y_new < screen_width) {
                int idx = getIndex(x_new, y_new);
                // use \geq to permit overlapping when z indexes are equal
                if(z_index >= buffer_z[idx]) {
                    buffer[idx] = image[i][j];
                    buffer_style[idx] = style;
                    buffer_z[idx] = z_index;
                }
            }
        }
    }
    return true;
}

void flush() {
    unsigned int size = screen_height * screen_width;
    for(unsigned int l = 0, r = 0; l < size; l = r) {
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

void clear() {
    unsigned int size = screen_height * screen_width;
    buffer = "";
    buffer.resize(size);
    // std::vector<Style>().swap(buffer_style);
    // buffer_style.resize(size);
    // std::vector<int>().swap(buffer_z);
    // buffer_z.resize(size);
    for(register int i = 0; i < size; ++i) {
        buffer_style[i] = default_style, buffer_z[i] = 0;
    }
}

void clearPart(int x, int y, int xx, int yy) {
    assert(0 <= x && x < xx && xx < screen_height && 0 <= y && y < yy && yy < screen_width);
    for(int i = x; i < xx; ++i) {
        for(int j = y; j < yy; ++j) {
            unsigned int idx = getIndex(i, j);
            buffer = ' ', buffer_style[idx] = default_style, buffer_z[idx] = 0;
        }
    }
}