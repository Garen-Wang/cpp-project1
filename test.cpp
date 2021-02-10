#include <memory>

#include "terminal.hpp"
#include "terminal.cpp"
#include "animation.hpp"
#include "animation.cpp"
#include "resources.cpp"


int main() {
    Terminal terminal;
    auto anim = std::make_shared<StillAnimation>(&terminal, images::x, terminal.getHeight() / 3, terminal.getWidth() / 4, 0, 0, 120, default_point, false);
    std::vector<std::shared_ptr<Animation>> vec;
    vec.push_back(anim);
    auto temp = vec[0];
    printf("%d\n", int(temp->getType()));
}