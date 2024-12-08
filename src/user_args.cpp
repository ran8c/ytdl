#include "ytdl/user_args.hpp"
#include "ytdl/presets.hpp"

#include <stdexcept>

#include <fmt/format.h>

using namespace ytdl;

/**
 * This function is broken up into a set of checks, any of which can throw a
 * `std::invalid_argument` if they fail.
 */
user_args::user_args user_args::parse(supported_presets& presets, int argc,
                                      char* argv[]) {  // NOLINT: argv is a c-style array
    user_args parsed_arguments{};

    // we need at two arguments, skipping argv[0]
    if (argc <= 2) {
        throw std::invalid_argument("not enough arguments given");
    }

    // first argument is always a preset
    try {
        parsed_arguments.selected_preset = presets.get_preset(argv[1]);  // NOLINT: pointer arithmetic is fine here
    } catch (const std::invalid_argument& err) {
        const std::string exception{fmt::format("failed to parse preset\n{}", err.what())};
        throw std::invalid_argument(exception);
    }

    // remaining arguments are urls
    for (int i = 2; i < argc; i++) {
        parsed_arguments.urls.emplace_back(argv[i]);  // NOLINT: pointer arithmetic is fine here
    }

    return parsed_arguments;
}

void user_args::user_args::print() {
    fmt::print("preset: {}\n", this->selected_preset.name);
    fmt::print("desc: {}\n", this->selected_preset.desc);

    // TODO: create a utility function out of this
    std::string flags_representation{"["};
    for (const auto& flag : this->selected_preset.flags) {
        flags_representation.append(fmt::format("{} ,", flag));
    }
    if (flags_representation.size() > 1) {
        flags_representation.resize(flags_representation.size() - 2);
    }
    flags_representation.append("]");

    fmt::print("flags: {}\n", flags_representation);

    std::string url_rep{"["};
    for (const auto& url : this->urls) {
        url_rep.append(fmt::format("{}, ", url));
    }
    if (url_rep.size() > 1) {
        url_rep.resize(url_rep.size() - 2);
    }
    url_rep.append("]");

    fmt::print("urls: {}\n", url_rep);
}
