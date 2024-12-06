#include "ytdl/env.hpp"

#include <iostream>

int main() {
    std::cout << "hello, world!\n";
    ytdl::env::ENV_VARS.print();
    return 0;
}