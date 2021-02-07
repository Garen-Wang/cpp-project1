#pragma once

#include <vector>
#include <string>

#include "terminal.hpp"
#include "terminal.cpp"

enum class Direction {
    Still,
    North,
    East,
    South,
    West,
    Northeast,
    Northwest,
    Southeast,
    Southwest
};

class Animation {
    public:
    // virtual function
};

class MoveAnimation : Animation {
    private:
        std::vector<std::string> &image;// main image in one animation
        unsigned int start_frame;// unit frame
        unsigned int duration;// unit: frame
        Terminal *terminal;// record terminal
        unsigned int x, y;// relative position to this terminal
        Direction direction;// move direction
        bool keep;// whether to keep last frame or not
    public:
        MoveAnimation(Terminal *terminal, std::vector<std::string> &image, Direction direction, unsigned int x=0, unsigned int y=0, unsigned int start_frame=0, unsigned int duration=120, bool keep=false);

};

class StillAnimation : public Animation {
    private:
        std::vector<std::string> &image;// main image in one animation
        unsigned int start_frame;// unit frame
        unsigned int duration;// unit: frame
        Terminal *terminal;// record terminal
        unsigned int x, y;// relative position to this terminal
        bool keep;// whether to keep last frame or not
    public:
        StillAnimation(Terminal *terminal, std::vector<std::string> &image, unsigned int x=0, unsigned int y=0, unsigned int start_frame=0, unsigned int duration=120, bool keep=false);

};

class Animations {
    public:
    // virtual function
};

class SequencialAnimations : public Animations {
    private:
        std::vector<Animation> &animations; // store instances of class Animation
        int duration;// unit: frame
    public:
        SequencialAnimations(std::vector<Animation> animations, unsigned int duration=120);
        void makeSequencialAnimations();
};

class ParallelAnimations : public Animations {
    private:
        std::vector<Animation> &animations;
        unsigned int duration;
    public:
        ParallelAnimations(std::vector<Animation> animations, unsigned int duration=120);
        void makeParallelAnimations();
};