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
        virtual unsigned int getFrames() = 0;
        virtual void generate(unsigned int t) = 0;
        virtual void debug() = 0;
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
        Style style;// style
        bool keep;// whether to keep last frame or not
    public:
        MoveAnimation(Terminal *terminal, std::vector<std::string> &image, Direction direction, int x=0, int y=0, int z=0, int v=1, unsigned int start_frame=0, unsigned int duration=120, Style style=default_style, bool keep=false);
        unsigned int getFrames();
        void generate(unsigned int t);
        void debug();
};

class StillAnimation : public Animation {
    private:
        std::vector<std::string> &image;// main image in one animation
        unsigned int start_frame;// unit frame
        unsigned int duration;// unit: frame
        Terminal *terminal;// record terminal
        int x, y;// relative position to this terminal
        int z;// z index
        Style style;// style
        bool keep;// whether to keep last frame or not
    public:
        StillAnimation(Terminal *terminal, std::vector<std::string> &image, int x=0, int y=0, int z=0, unsigned int start_frame=0, unsigned int duration=120, Style style=default_style, bool keep=false);
        unsigned int getFrames();
        void generate(unsigned int t);
        void debug();
};

class SequencialAnimation : public Animation {
    private:
        std::vector<std::shared_ptr<Animation>> animations; // store instances of class Animation
        unsigned int duration;// unit: frame
    public:
        SequencialAnimation(std::vector<std::shared_ptr<Animation>> animations, unsigned int duration=120);
        unsigned int getFrames();
        void generate(unsigned int t);
        void debug();
};

class ParallelAnimation : public Animation {
    private:
        std::vector<std::shared_ptr<Animation>> animations;
        unsigned int duration;
    public:
        ParallelAnimation(std::vector<std::shared_ptr<Animation>> animations, unsigned int duration=120);
        unsigned int getFrames();
        void generate(unsigned int t);
        void debug();
};
