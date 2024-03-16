#include "Program.h"

#include <random>

int main(int argc, char* argv[]) {
    Program prog;

    std::random_device rd;
    std::mt19937 mt(rd());

    while (prog.is_running()) {
        prog.events();
        prog.render(mt);
    }

    return 0;
}