#pragma once

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "terminal.hpp"

// first: width, second: height
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
    return std::make_pair(width, height);
}

// constructor of actual terminal
Terminal::Terminal():
offset_width(0), offset_height(0) {
    this->parent = nullptr;
    auto temp = get_terminal_size();
    this->width = temp.first;
    this->height = temp.second;
}

// constructor of subterminal
Terminal::Terminal(Terminal *parent, unsigned int width, unsigned int height, unsigned int offset_width, unsigned int offset_height):
parent(parent), width(width), height(height), offset_width(offset_width), offset_height(offset_height) {

}

// destructor
Terminal::~Terminal() {

}

unsigned int Terminal::getWidth() {
    return this->width;
}
unsigned int Terminal::getHeight() {
    return this->height;
}
bool Terminal::isActual() {
    return parent == nullptr;
}

void Terminal::print() {

}

void Terminal::clear() {

}