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

void predraw() {
    clear();
}

Types Animation::getType() {
    return Types::Base;
}
Types StillAnimation::getType() {
    return Types::Still;
}
Types MoveAnimation::getType() {
    return Types::Move;
}
Types SequencialAnimation::getType() {
    return Types::Sequencial;
}
Types ParallelAnimation::getType() {
    return Types::Parallel;
}
Types Animations::getType() {
    return Types::Base;
}
Types SequencialAnimations::getType() {
    return Types::Sequencial;
}
Types ParallelAnimations::getType() {
    return Types::Parallel;
}

// class MoveAnimation
MoveAnimation::MoveAnimation(Terminal *terminal, std::vector<std::string> &image, Direction direction, int x, int y, int z, int v, unsigned int start_frame, unsigned int duration, Point style, bool keep):
terminal(terminal), image(image), direction(direction), x(x), y(y), z(z), v(v), start_frame(start_frame), duration(duration), style(style), keep(keep) {}

void MoveAnimation::generate() {

}

void MoveAnimation::debug() {
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
    
}

void StillAnimation::debug() {
    unsigned int last_frame = start_frame + duration;
    for(int t = 0; t < last_frame; t++) {
        usleep(per_frame);
        if(t >= start_frame) {
            predraw();
            bool res = terminal->print(image, x, y, style, z);
            if(res) flush();
        }
    }
}

// class SequencialAnimation
SequencialAnimation::SequencialAnimation(std::vector<std::shared_ptr<Animation>> animations, unsigned int duration):
animations(animations), duration(duration) {}

void SequencialAnimation::generate() {

}

void SequencialAnimation::debug() {
    
}

// class ParallelAnimation

ParallelAnimation::ParallelAnimation(std::vector<std::shared_ptr<Animation>> animations, unsigned int duration):
animations(animations), duration(duration) {}

void ParallelAnimation::generate() {

}

void ParallelAnimation::debug() {

}

// class SequencialAnimations
SequencialAnimations::SequencialAnimations(std::vector<std::shared_ptr<Animations>> animations, unsigned int duration):
animations(animations), duration(duration) {}

void SequencialAnimations::generate() {
    
}

void SequencialAnimations::debug() {

}

// class ParallelAnimation

ParallelAnimations::ParallelAnimations(std::vector<std::shared_ptr<Animations>> animations, unsigned int duration):
animations(animations), duration(duration) {}

void ParallelAnimations::generate() {

}

void ParallelAnimations::debug() {

}