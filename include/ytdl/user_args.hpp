#ifndef YTDL_YTDL_USER_ARGS_HPP
#define YTDL_YTDL_USER_ARGS_HPP

#include <string>
#include <vector>

#include "ytdl/presets.hpp"

using namespace ytdl::presets;

namespace ytdl::user_args
{

/**
 * A set of successfully parsed user arguments.
 */
struct user_args
{
    /**
     * A preset selected by the user.
     */
    preset selected_preset;

    /**
     * A list of URLs given by the user.
     */
    std::vector<std::string> urls;

    /**
     * Prints the contents of this `user_args` instance.
     *
     * This is used for debugging.
     *
     * Causes UB if this `user_args` instance is malformed.
     */
    void print();
};

/**
 * @brief Parses `argv` and `argc` into a `user_args`.
 * @param `supported_presets`: a set of presets to parse.
 * @param `int`: the program's `argc`.
 * @param `char*[]`: the program's `argv`
 * @throw `std::invalid_argument` if parsing fails.
 */
user_args parse(supported_presets&,
                int,
                char*[]);  // NOLINT: argv is always a c-style array

}  // namespace ytdl::user_args

#endif
