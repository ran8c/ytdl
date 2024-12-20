#ifndef YTDL_YTDL_UTILS_HPP
#define YTDL_YTDL_UTILS_HPP

#include <string>
#include <vector>

namespace ytdl::utils
{

/**
 * @brief Creates a string representation of a string vector.
 * @param `std::vector<std::string>&`: The vector to represent.
 *
 * This is intended for print debugging.
 */
std::string rep_str_vec(const std::vector<std::string> &);

} // namespace ytdl::utils

#endif
