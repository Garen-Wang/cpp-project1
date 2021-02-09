#pragma once

#include <vector>
#include <string>

#include "animation.hpp"
#include "terminal.hpp"
#include "terminal.cpp"
// time unit: frame, 33000 milliseconds per frame
// use terminal.print, terminal.flush, terminal.clear
// as for position, use percent to expand scalibility

void predraw() {
    clear();
}
// class MoveAnimation
MoveAnimation::MoveAnimation(Terminal *terminal, std::vector<std::string> &image, Direction direction, int x, int y, int z, unsigned int start_frame, unsigned int duration, Point style, bool keep):
terminal(terminal), image(image), direction(direction), x(x), y(y), z(z), start_frame(start_frame), duration(duration), style(style), keep(keep) {}

void MoveAnimation::generate() {
    unsigned int last_frame = start_frame + duration;
    for(int t = 0; t < last_frame; t++) {
        usleep(33000);
        if(t >= start_frame) {
            predraw();
            int v = 1;
            terminal->print(image, x, y, style, z);
            flush();
            x += v * dx[int(direction)];
            y += v * dy[int(direction)];
        }
    }
}

// class StillAnimation
StillAnimation::StillAnimation(Terminal *terminal, std::vector<std::string> &image, int x, int y, int z, unsigned int start_frame, unsigned int duration, Point style, bool keep):
terminal(terminal), image(image), x(x), y(y), z(z), start_frame(start_frame), duration(duration), style(style), keep(keep) {}

void StillAnimation::generate() {
    unsigned int last_frame = start_frame + duration;
    for(int t = 0; t < last_frame; t++) {
        usleep(33000);
        if(t >= start_frame) {
            predraw();
            terminal->print(image, x, y, style, z);
            flush();
        }
    }
}