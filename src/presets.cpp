#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "ytdl/presets.hpp"

#include <fmt/format.h>

#include "ytdl/utils.hpp"

namespace presets = ytdl::presets;

/**
 * Constructor for `presets::supported_presets`.
 */
presets::supported_presets::supported_presets(
    const std::vector<preset>& presets)
    : preset_list(presets)
{
}

/**
 * Getter for a `preset` in `presets::supported_presets.preset_list`.
 */
presets::preset& presets::supported_presets::get_preset(
    const std::string_view& selected_preset)
{
    // `std::find_if()` exists, but this method is easier for me to read
    for (auto& preset : this->preset_list) {
        if (preset.name == selected_preset) {
            return preset;
        }
    }
    const std::string exception {
        fmt::format(R"(preset "{}" not supported)", selected_preset)};
    throw std::invalid_argument(exception);
}

/**
 * Debug print out `presets::supported_presets.preset_list`.
 */
void presets::supported_presets::print()
{
    for (const auto& preset : this->preset_list) {
        std::cout << fmt::format(
            "[{}, {}]\n", preset.name, utils::rep_str_vec(preset.flags));
    }
}
