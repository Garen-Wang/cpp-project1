#pragma once

#include <vector>
#include <string>

#include "terminal.hpp"
#include "terminal.cpp"

enum class Direction {
    Still = 0,
    Up = 1,
    Down = 2,
    Left = 3,
    Right = 4
};
const int dx[] = {0, -1, 1, 0, 0};
const int dy[] = {0, 0, 0, -1, 1};

class Animation {
    public:
        virtual void generate() = 0;
};

class MoveAnimation : public Animation {
    private:
        std::vector<std::string> &image;// main image in one animation
        unsigned int start_frame;// unit frame
        unsigned int duration;// unit: frame
        Terminal *terminal;// record terminal
        int x, y;// relative position to this terminal
        int z;// z index
        int v;// moving velocity
        Direction direction;// move direction
        Point style;// style
        bool keep;// whether to keep last frame or not
    public:
        MoveAnimation(Terminal *terminal, std::vector<std::string> &image, Direction direction, int x=0, int y=0, int z=0, int v=5, unsigned int start_frame=0, unsigned int duration=120, Point style=default_point, bool keep=false);
        void generate();
};

class StillAnimation : public Animation {
    private:
        std::vector<std::string> &image;// main image in one animation
        unsigned int start_frame;// unit frame
        unsigned int duration;// unit: frame
        Terminal *terminal;// record terminal
        int x, y;// relative position to this terminal
        int z;// z index
        Point style;// style
        bool keep;// whether to keep last frame or not
    public:
        StillAnimation(Terminal *terminal, std::vector<std::string> &image, int x=0, int y=0, int z=0, unsigned int start_frame=0, unsigned int duration=120, Point style=default_point, bool keep=false);
        void generate();
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

void predraw();