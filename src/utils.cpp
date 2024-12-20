#include <string>
#include <vector>

#include "ytdl/utils.hpp"

#include <fmt/format.h>

namespace utils = ytdl::utils;

std::string utils::rep_str_vec(const std::vector<std::string> &vec)
{
    // [item, item, item]

    std::string output{"["};
    for (const auto &str : vec)
    {
        output.append(fmt::format("{}, ", str));
    }
    // remove last comma and space
    if (output.size() > 1)
    {
        output.resize(output.size() - 2);
    }
    output.append("]");

    return output;
}
