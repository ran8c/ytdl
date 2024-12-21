#ifndef YTDL_YTDL_DOWNLOAD_HPP
#define YTDL_YTDL_DOWNLOAD_HPP

#include <string_view>

#include "ytdl/presets.hpp"

namespace ytdl::download
{

/**
 * @brief Download a URL with a preset.
 * @param `presets::preset`: a valid preset.
 * @param `std::string_view`: a URL to download.
 * @throw `std::runtime_error` if the downloader exited with an error.
 */
void download(const presets::preset &, const std::string_view &);

} // namespace ytdl::download

#endif
