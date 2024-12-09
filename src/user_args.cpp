#include <stdexcept>
#include <string>

#include "ytdl/user_args.hpp"

#include <fmt/base.h>
#include <fmt/format.h>

#include "ytdl/presets.hpp"
#include "ytdl/utils.hpp"

namespace user_args = ytdl::user_args;

/**
 * This function is broken up into a set of checks, any of which can throw a
 * `std::invalid_argument` if they fail.
 */
user_args::user_args user_args::parse(
    supported_presets& presets,
    int argc,
    char* argv[])  // NOLINT: argv is always a c-style array
{
    user_args parsed_arguments {};

    // we need at two arguments, skipping argv[0]
    if (argc <= 2) {
        throw std::invalid_argument("not enough arguments given");
    }

    // first argument is always a preset
    try {
        parsed_arguments.selected_preset = presets.get_preset(
            argv[1]);  // NOLINT: pointer arithmetic is fine here
    } catch (const std::invalid_argument& err) {
        const std::string exception {
            fmt::format("failed to parse preset\n{}", err.what())};
        throw std::invalid_argument(exception);
    }

    // remaining arguments are urls
    for (int i = 2; i < argc; i++) {
        parsed_arguments.urls.emplace_back(
            argv[i]);  // NOLINT: pointer arithmetic is fine here
    }

    return parsed_arguments;
}

void user_args::user_args::print()
{
    fmt::print("preset: {}\n", this->selected_preset.name);
    fmt::print("desc: {}\n", this->selected_preset.desc);
    fmt::print("flags: {}\n", utils::rep_str_vec(this->selected_preset.flags));
    fmt::print("urls: {}\n", utils::rep_str_vec(this->urls));
}
