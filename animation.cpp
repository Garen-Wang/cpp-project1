#pragma once

#include "animation.hpp"
// time unit: frame, 33333 microseconds per frame
// use terminal.print, terminal.flush, terminal.clear
// as for position, use percent to expand scalibility

// MoveAnimation
MoveAnimation::MoveAnimation(Terminal *terminal, std::vector<std::string> &image, Direction direction, unsigned int x=0u, unsigned int y=0u, unsigned int start_frame=0u, unsigned int duration=120u, Point style=default_point, bool keep=false):
terminal(terminal), image(image), direction(direction), x(x), y(y), start_frame(start_frame), duration(duration), style(style), keep(keep) {}

void MoveAnimation::generate() {
    
}

// StillAnimation
StillAnimation::StillAnimation(Terminal *terminal, std::vector<std::string> &image, unsigned int x=0u, unsigned int y=0u, unsigned int start_frame=0u, unsigned int duration=120u, Point style=default_point, bool keep=false):
terminal(terminal), image(image), x(x), y(y), start_frame(start_frame), duration(duration), style(style), keep(keep) {}

void StillAnimation::generate() {
    for(int t = 0; t < duration; ++t) {
        usleep(33333);
        clear();
        terminal->print(image, x, y, style, 0);
        flush();
    }
}

// Animations
void Animations::play() {

}

// SequencialAnimations
SequencialAnimations::SequencialAnimations(std::vector<Animation*> animations, unsigned int duration=120) : animations(animations), duration(duration) {}

// ParallelAnimations
ParallelAnimations::ParallelAnimations(std::vector<Animation*> animations, unsigned int duration=120) : animations(animations), duration(duration) {}
