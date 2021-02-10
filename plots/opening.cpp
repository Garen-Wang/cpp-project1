#include <memory>

#include "../terminal.hpp"
#include "../terminal.cpp"
#include "../animation.hpp"
#include "../animation.cpp"
#include "../resources.cpp"

namespace opening {
    Style green_style = {TextAttribute::Default, Foreground::Green, Background::Default};
    Style red_style = {TextAttribute::Default, Foreground::Red, Background::Default};
    Style blue_style = {TextAttribute::Default, Foreground::Blue, Background::Default};
    // cannot pass pointer for 
    void show(Terminal *terminal) {
        unsigned int height = terminal->getHeight(), width = terminal->getWidth();

        auto letter_x = std::make_shared<StillAnimation>(terminal, images::letter_x, height / 3, width / 4  - 6, 0, 0, 150, default_style, true);
        auto letter_k = std::make_shared<StillAnimation>(terminal, images::letter_k, height / 3, width / 2 - 6, 0, 30, 120, red_style, true);
        auto letter_c = std::make_shared<StillAnimation>(terminal, images::letter_c, height / 3, width * 3 / 4 - 6, 0, 60, 90, blue_style, true);
        auto letter_d = std::make_shared<StillAnimation>(terminal, images::letter_d, height / 3, width - 6, 0, 90, 60, green_style, true);
        auto number_505 = std::make_shared<StillAnimation>(terminal, images::number_505, height * 3 / 4, width / 4 + 6, 0, 120, 30, default_style, true);
        std::vector<std::shared_ptr<Animation>> vec1 = {letter_x, letter_k, letter_c, letter_d, number_505};
        // auto temp1 = ParallelAnimation(vec1);
        auto temp1 = std::make_shared<ParallelAnimation>(vec1);

        auto letter_xx = std::make_shared<MoveAnimation>(terminal, images::letter_x, Direction::Left, height / 3, width / 4 - 6, 0, 1, 0, 120, default_style);
        auto letter_kk = std::make_shared<MoveAnimation>(terminal, images::letter_k, Direction::Up, height / 3, width / 2 - 6, 0, 1, 0, 120, red_style);
        auto letter_cc = std::make_shared<MoveAnimation>(terminal, images::letter_c, Direction::Up, height / 3, width * 3 / 4 - 6, 0, 1, 0, 120, blue_style);
        auto letter_dd = std::make_shared<MoveAnimation>(terminal, images::letter_d, Direction::Right, height / 3, width - 6, 0, 1, 0, 120, green_style);
        auto number_505505 = std::make_shared<MoveAnimation>(terminal, images::number_505, Direction::Down, height * 3 / 4, width / 4 + 6, 0, 1, 0, 120, default_style);
        std::vector<std::shared_ptr<Animation>> vec2 = {letter_xx, letter_kk, letter_cc, letter_dd, number_505505};
        // auto temp2 = ParallelAnimation(vec2);
        auto temp2 = std::make_shared<ParallelAnimation>(vec2);

        // temp1->debug();
        // temp2->debug();
        std::vector<std::shared_ptr<Animation>> vec3 = {temp1, temp2};
        auto temp = std::make_shared<SequencialAnimation>(vec3);
        temp->debug();
    }
};