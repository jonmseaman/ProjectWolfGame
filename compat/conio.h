// POSIX stub for <conio.h> — provides _getch() used by Engine/UI/Input.cpp.
// Only included on non-Windows builds; on Windows the real <conio.h> is used.
#pragma once
#include <termios.h>
#include <unistd.h>

inline int _getch() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
