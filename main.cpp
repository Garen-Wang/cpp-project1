#include "terminal.cpp"
#include "terminal.hpp"

int main() {
    Terminal terminal;
    unsigned int width = terminal.getWidth();
    unsigned int height = terminal.getHeight();
    printf("%u %u\n", width, height);
    return 0;
}