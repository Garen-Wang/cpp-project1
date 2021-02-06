
#include <termios.h>
#include <unistd.h>
#include "terminal.hpp"


std::pair<unsigned int, unsigned int> get_terminal_size() {
    unsigned int width, height;
    printf("\033[2077;2077H\033[6n");
    scanf("\033[%d;%dR", &width, &height);
    return std::make_pair(width, height);
}

int main() {
    termios init_setting, new_setting;
    tcgetattr(STDIN_FILENO, &init_setting);
    new_setting = init_setting;
    new_setting.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_setting);
    printf("sbsbsbsbsb\n");
    char ch[1005];
    fgets(ch, 1005, stdin);
    puts(ch);

    // reset
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &init_setting);
}
