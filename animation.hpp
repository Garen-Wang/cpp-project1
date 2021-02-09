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

};

class MoveAnimation : public Animation {
    private:
        std::vector<std::string> &image;// main image in one animation
        unsigned int start_frame;// unit frame
        unsigned int duration;// unit: frame
        Terminal *terminal;// record terminal
        unsigned int x, y;// relative position to this terminal
        Direction direction;// move direction
        Point style;// style
        bool keep;// whether to keep last frame or not
    public:
        MoveAnimation(Terminal *terminal, std::vector<std::string> &image, Direction direction, unsigned int x=0u, unsigned int y=0u, unsigned int start_frame=0u, unsigned int duration=120u, Point style=default_point, bool keep=false);
        void generate();

};

class StillAnimation : public Animation {
    private:
        std::vector<std::string> &image;// main image in one animation
        unsigned int start_frame;// unit frame
        unsigned int duration;// unit: frame
        Terminal *terminal;// record terminal
        unsigned int x, y;// relative position to this terminal
        Point style;// style
        bool keep;// whether to keep last frame or not
    public:
        StillAnimation(Terminal *terminal, std::vector<std::string> &image, unsigned int x=0u, unsigned int y=0u, unsigned int start_frame=0u, unsigned int duration=120u, Point style=default_point, bool keep=false);
        void generate();

};

class Animations {
    public:
    virtual void play() = 0;
};

class SequencialAnimations : public Animations {
    private:
        std::vector<Animation*> &animations; // store instances of class Animation
        unsigned int duration;// unit: frame
    public:
        SequencialAnimations(std::vector<Animation*> animations, unsigned int duration=120u);
        void makeSequencialAnimations();
};

class ParallelAnimations : public Animations {
    private:
        std::vector<Animation*> &animations;
        unsigned int duration;
    public:
        ParallelAnimations(std::vector<Animation*> animations, unsigned int duration=120u);
        void makeParallelAnimations();
};
