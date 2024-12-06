#include "ytdl/env.hpp"
#include "ytdl/presets.hpp"

int main() {
    ytdl::env::ENV_VARS.print();
    ytdl::presets::PRESET_LIST.print();
    return 0;
}