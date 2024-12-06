#include "ytdl/presets.hpp"

#include <iostream>

#include <boost/format.hpp>

using namespace ytdl::presets;

namespace {

std::string print_vector(const std::vector<std::string>& vec) {
    boost::format vector_template{"%1%, "};
    std::string output{"["};
    for (const auto& item : vec) {
        output.append(boost::str(vector_template % item));
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
    auto exception{boost::format("preset \"%1%\" not supported") % selected_preset};
    throw std::invalid_argument(exception.str());
}

void supported_presets::print() {
    for (const auto& preset : this->preset_list) {
        std::cout << boost::format("[%1%, %2%]\n") % preset.name % print_vector(preset.flags);
    }
}