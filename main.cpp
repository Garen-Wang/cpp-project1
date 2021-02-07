#include "terminal.cpp"
#include "terminal.hpp"
#include "resources.cpp"

int main() {
    Terminal terminal;
    printf("%u %u\n", terminal.getHeight(), terminal.getWidth());

    // if width is odd, it works.
    Terminal up_terminal(&terminal, terminal.getHeight() * 2 / 3, terminal.getWidth(), 0, 0);
    Terminal down_terminal(&terminal, terminal.getHeight() / 3, terminal.getWidth(), terminal.getHeight() * 2 / 3 + 1, 0);
    // if width is even, it works.
    // Terminal up_terminal(&terminal, terminal.getHeight() / 2, terminal.getWidth(), 0, 0);
    // Terminal down_terminal(&terminal, terminal.getHeight() / 2, terminal.getWidth(), terminal.getHeight() / 2 + 1, 0);

    up_terminal.print(imageX, 0, 0, default_point, 0);
    down_terminal.print(imageX, 0, 0, default_point, 0);

    for(int t = 0; t < 120; ++t) {
        usleep(33333);
        terminal.flush();
    }
}