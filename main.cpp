#include <memory>

#include "plots/opening.cpp"
#include "terminal.hpp"
#include "terminal.cpp"
#include "animation.hpp"
#include "animation.cpp"
#include "resources.cpp"

namespace example1 {
    int main() {
        Terminal terminal;
        // if width is odd, it works.
        Terminal up_terminal(&terminal, terminal.getHeight() * 2 / 3, terminal.getWidth(), 0, 0);
        Terminal down_terminal(&terminal, terminal.getHeight() / 3, terminal.getWidth(), terminal.getHeight() * 2 / 3 + 1, 0);
        // if width is even, it works.
        // Terminal up_terminal(&terminal, terminal.getHeight() / 2, terminal.getWidth(), 0, 0);
        // Terminal down_terminal(&terminal, terminal.getHeight() / 2, terminal.getWidth(), terminal.getHeight() / 2 + 1, 0);

        Style special_style = {
            TextAttribute::Blink, Foreground::Cyan, Background::Default
        };
        up_terminal.print(images::letter_x, 5, 10, default_style, 1);
        down_terminal.print(images::letter_x, 5, 40, special_style, 1);
        up_terminal.print(images::letter_x, 5, 10, special_style, 2);
        down_terminal.print(images::letter_x, 5, 40, default_style, 2);
        flush();
        return 0;
    }
};

int main() {
    Terminal terminal;
    opening::show(&terminal);
    return 0;
}
