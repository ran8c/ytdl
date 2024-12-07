#include "ytdl/env.hpp"
#include "ytdl/presets.hpp"
#include "ytdl/user_args.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    // currently, just print out debugging information
    ytdl::env::ENV_VARS.print();
    ytdl::presets::PRESET_LIST.print();

    ytdl::user_args::user_args user_args;
    try {
        user_args = ytdl::user_args::parse(PRESET_LIST, argc, argv);
    } catch (const std::invalid_argument& err) {
        std::cerr << err.what() << "\n";
        return 1;
    }
    user_args.print();

    return 0;
}
