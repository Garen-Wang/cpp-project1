#pragma once

#include <vector>
#include <string>
#include <memory>

#include "animation.hpp"
#include "terminal.hpp"
#include "terminal.cpp"
// time unit: frame
// use terminal.print, terminal.flush, terminal.clear
// as for position, use percent to expand scalibility

unsigned int per_frame = 40000;// about 24 frames per second

unsigned int StillAnimation::getFrames() {
    return start_frame + duration;
}
unsigned int MoveAnimation::getFrames() {
    return start_frame + duration;
}
unsigned int SequencialAnimation::getFrames() {
    return duration;
}
unsigned int ParallelAnimation::getFrames() {
    return duration;
}

// class MoveAnimation
MoveAnimation::MoveAnimation(Terminal *terminal, std::vector<std::string> &image, Direction direction, int x, int y, int z, int v, unsigned int start_frame, unsigned int duration, Style style, bool keep):
terminal(terminal), image(image), direction(direction), x(x), y(y), z(z), v(v), start_frame(start_frame), duration(duration), style(style), keep(keep) {}

void MoveAnimation::generate(unsigned int t) {
    if(t >= start_frame && t < start_frame + duration) {
        int xx = x + v * (t - start_frame) * dx[int(direction)];
        int yy = y + v * (t - start_frame) * dy[int(direction)];
        terminal->print(image, xx, yy, style, z);
    } else if(keep && t >= start_frame + duration) {
        int xx = x + v * (duration - 1) * dx[int(direction)];
        int yy = y + v * (duration - 1) * dy[int(direction)];
        terminal->print(image, xx, yy, style, z);
    }
}

void MoveAnimation::debug() {
    unsigned int last_frame = start_frame + duration;
    for(int t = 0; t < last_frame; t++) {
        usleep(per_frame);
        if(t >= start_frame) {
            clear();
            bool res = terminal->print(image, x, y, style, z);
            if(res) flush();
            x += v * dx[int(direction)];
            y += v * dy[int(direction)];
        }
    }
}

// class StillAnimation
StillAnimation::StillAnimation(Terminal *terminal, std::vector<std::string> &image, int x, int y, int z, unsigned int start_frame, unsigned int duration, Style style, bool keep):
terminal(terminal), image(image), x(x), y(y), z(z), start_frame(start_frame), duration(duration), style(style), keep(keep) {}

void StillAnimation::generate(unsigned int t) {
    if(start_frame <= t && t < start_frame + duration || keep && t >= start_frame) {
        terminal->print(image, x, y, style, z);
    }
}

void StillAnimation::debug() {
    unsigned int last_frame = start_frame + duration;
    for(int t = 0; t < last_frame; t++) {
        usleep(per_frame);
        if(t >= start_frame) {
            clear();
            bool res = terminal->print(image, x, y, style, z);
            if(res) flush();
        }
    }
}

// class SequencialAnimation
SequencialAnimation::SequencialAnimation(std::vector<std::shared_ptr<Animation>> animations, unsigned int duration):
animations(animations), duration(duration) {}

void SequencialAnimation::generate(unsigned int t) {
    unsigned int total_frame = 0;
    for(auto it : animations) {
        if(t < total_frame + it->getFrames()) {
            it->generate(t);
            return;
        }
        total_frame += it->getFrames();
    }
}

void SequencialAnimation::debug() {
    unsigned int total_frame = 0;
    for(auto it : animations) {
        unsigned int last_frame = it->getFrames();
        for(unsigned int t = 0; t < last_frame; ++t) {
            usleep(per_frame);
            clear();
            it->generate(t);
            flush();
        }
        total_frame += last_frame;
    }
}

// class ParallelAnimation

ParallelAnimation::ParallelAnimation(std::vector<std::shared_ptr<Animation>> animations, unsigned int duration):
animations(animations), duration(duration) {}

void ParallelAnimation::generate(unsigned int t) {
    for(auto it : animations) it->generate(t);
}

void ParallelAnimation::debug() {
    unsigned int last_frame = duration;
    for(auto it : animations) {
        last_frame = std::max(last_frame, it->getFrames());
    }
    for(unsigned int t = 0; t < last_frame; ++t) {
        usleep(per_frame);
        clear();
        for(auto it : animations) it->generate(t);
        flush();
    }
}
