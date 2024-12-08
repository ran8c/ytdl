#include "ytdl/presets.hpp"
#include "ytdl/utils.hpp"

#include <string>
#include <vector>
#include <string_view>
#include <stdexcept>
#include <iostream>

#include <fmt/format.h>

using namespace ytdl;

presets::supported_presets::supported_presets(const std::vector<preset>& presets) : preset_list(presets) {}

presets::preset& presets::supported_presets::get_preset(const std::string_view& selected_preset) {
    for (auto& preset : this->preset_list) {
        if (preset.name == selected_preset) {
            return preset;
        }
    }
    const std::string exception{fmt::format(R"(preset "{}" not supported)", selected_preset)};
    throw std::invalid_argument(exception);
}

void presets::supported_presets::print() {
    for (const auto& preset : this->preset_list) {
        std::cout << fmt::format("[{}, {}]\n", preset.name, utils::rep_str_vec(preset.flags));
    }
}
