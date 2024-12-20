#ifndef YTDL_YTDL_URL_PARSING_HPP
#define YTDL_YTDL_URL_PARSING_HPP

#include <string>

namespace ytdl::url_parsing
{

/**
 * @brief Parses a URL and returns a clean, redirected URL.
 * @param `std::string_view`: the URL to parse.
 * @throw `std::out_of_range` if the URL given is blank.
 * @throw `std::invalid_argument` if the URL failed to parse.
 * @throw `std::runtime_error` if the resulting URL isn't valid (report this).
 */
std::string redirect_url(const std::string_view &);

} // namespace ytdl::url_parsing

#endif
