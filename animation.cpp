#pragma once

#include <vector>
#include <string>

#include "animation.hpp"
#include "terminal.hpp"
#include "terminal.cpp"
// time unit: frame
// use terminal.print, terminal.flush, terminal.clear
// as for position, use percent to expand scalibility

unsigned int per_frame = 40000;// about 24 frames per second

void predraw() {
    clear();
}
// class MoveAnimation
MoveAnimation::MoveAnimation(Terminal *terminal, std::vector<std::string> &image, Direction direction, int x, int y, int z, int v, unsigned int start_frame, unsigned int duration, Point style, bool keep):
terminal(terminal), image(image), direction(direction), x(x), y(y), z(z), v(v), start_frame(start_frame), duration(duration), style(style), keep(keep) {}

void MoveAnimation::generate() {
    unsigned int last_frame = start_frame + duration;
    for(int t = 0; t < last_frame; t++) {
        usleep(per_frame);
        if(t >= start_frame) {
            predraw();
            bool res = terminal->print(image, x, y, style, z);
            if(res) flush();
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
        usleep(per_frame);
        if(t >= start_frame) {
            predraw();
            terminal->print(image, x, y, style, z);
            flush();
        }
    }
}

// class SequencialAnimation
SequencialAnimation::SequencialAnimation(std::vector<Animation *> animations, unsigned int duration=120):
animations(animations), duration(duration) {}

void SequencialAnimation::generate() {

}

// class ParallelAnimation

ParallelAnimation::ParallelAnimation(std::vector<Animation *> animations, unsigned int duration=120):
animations(animations), duration(duration) {}

void ParallelAnimation::generate() {

}

// class SequencialAnimations
SequencialAnimations::SequencialAnimations(std::vector<Animations *> animations, unsigned int duration=120):
animations(animations), duration(duration) {}

void SequencialAnimations::generate() {
    
}

// class ParallelAnimation

ParallelAnimations::ParallelAnimations(std::vector<Animations *> animations, unsigned int duration=120):
animations(animations), duration(duration) {}

void ParallelAnimations::generate() {

}