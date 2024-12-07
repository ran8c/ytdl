#include "ytdl/presets.hpp"

#include <string>
#include <vector>
#include <string_view>
#include <stdexcept>
#include <iostream>

#include <fmt/format.h>

using namespace ytdl::presets;

namespace {

std::string print_vector(const std::vector<std::string>& vec) {
    std::string output{"["};
    for (const auto& item : vec) {
        output.append(fmt::format("{}, ", item));
    }
    // remove the last comma and space
    if (output.size() > 1) {
        output.resize(output.size() - 2);
    }
    output.append("]");
    return output;
}

}  // namespace

supported_presets::supported_presets(const std::vector<preset>& presets) : preset_list(presets) {}

preset& supported_presets::get_preset(const std::string_view& selected_preset) {
    for (auto& preset : this->preset_list) {
        if (preset.name == selected_preset) {
            return preset;
        }
    }
    const std::string exception{fmt::format(R"(preset "{}" not supported)", selected_preset)};
    throw std::invalid_argument(exception);
}

void supported_presets::print() {
    for (const auto& preset : this->preset_list) {
        std::cout << fmt::format("[{}, {}]\n", preset.name, print_vector(preset.flags));
    }
}
