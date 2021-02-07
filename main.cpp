#include "terminal.cpp"
#include "terminal.hpp"
#include "resources.cpp"

int main() {
    Terminal terminal;

    // if width is odd, it works.
    Terminal up_terminal(&terminal, terminal.getHeight() * 2 / 3, terminal.getWidth(), 0, 0);
    Terminal down_terminal(&terminal, terminal.getHeight() / 3, terminal.getWidth(), terminal.getHeight() * 2 / 3 + 1, 0);
    // if width is even, it works.
    // Terminal up_terminal(&terminal, terminal.getHeight() / 2, terminal.getWidth(), 0, 0);
    // Terminal down_terminal(&terminal, terminal.getHeight() / 2, terminal.getWidth(), terminal.getHeight() / 2 + 1, 0);

    Point special_point = {
        TextAttribute::Blink, Foreground::Cyan, Background::Default
    };
    up_terminal.print(images::x, 5, 10, default_point, 1);
    down_terminal.print(images::x, 5, 40, special_point, 1);
    up_terminal.print(images::x, 5, 10, special_point, 2);
    down_terminal.print(images::x, 5, 40, default_point, 2);
    terminal.flush();
    // system("clear");
    return 0;
}