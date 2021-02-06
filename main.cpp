#include "terminal.cpp"
#include "terminal.hpp"
#include "resources.cpp"

int main() {
    Terminal terminal;
    auto temp1 = screen[0];
    auto temp2 = screen_style[0];
    printf("%d\n", temp1);
    printf("%d %d %d\n", temp2.text_attribute, temp2.foreground, temp2.background);
}