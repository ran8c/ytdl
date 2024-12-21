#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "ytdl/download.hpp"

#include <boost/asio/io_context.hpp>
#include <boost/process/v2/environment.hpp>
#include <boost/process/v2/process.hpp>
#include <fmt/format.h>

#include "ytdl/presets.hpp"

namespace download = ytdl::download;

/**
 * The binary name of the downloader to call.
 *
 * macOS (`__APPLE__`) and Linux (`__unix__`) share the same binary name;
 * Windows (`_WIN32`) requires a `.exe` extension to the binary name.
 */
const constexpr char *downloader{
#ifdef _WIN32
    "yt-dlp.exe"
#elif __unix__ || __APPLE__
    "yt-dlp"
#endif
};

void download::download(const presets::preset &preset, const std::string_view &url)
{
    // find the downloader
    const auto downloader_path{boost::process::environment::find_executable(downloader)};
    if (downloader_path.empty())
    {
        const std::string msg{fmt::format(R"(failed to find downloader "{}")", downloader)};
        throw std::runtime_error(msg);
    }

    // merge the args together, boost.process expects that
    std::vector<std::string> downloader_args{preset.flags};
    downloader_args.emplace_back(url);

    // io_executor handles stdin and stdout for downloader
    boost::asio::io_context io_executor;

    // build the syscall
    boost::process::process downloader_process{io_executor, downloader_path, downloader_args};

    // run the syscall
    const int downloader_process_code{downloader_process.wait()};
    if (downloader_process_code != 0)
    {
        const std::string msg{fmt::format("{} exited with code {}", downloader, downloader_process_code)};
        throw std::runtime_error(msg);
    }
}
