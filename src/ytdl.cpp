#include <cstdint>
#include <iostream>
#include <stdexcept>

#include "ytdl/download.hpp"
#include "ytdl/env.hpp"
#include "ytdl/presets.hpp"
#include "ytdl/url_parsing.hpp"
#include "ytdl/user_args.hpp"

// NOLINTNEXTLINE: this file is a sole consumer, not part of a library
using namespace ytdl;

enum err_codes : std::int8_t
{
    expected_err = 1,
    unexpected_err = -1,
};

int main(int argc, char *argv[])
{
    // get supported environment variables
    env::current_env_vars env_vars{{"DEBUG", "VERBOSE"}};

    // create list of supported presets
    presets::supported_presets preset_list{{
        // presets related to audio
        presets::preset{
            .name{"audio"},
            .desc{"Extract and format audio from URLs"},
            .flags{
                "--extract-audio",
                "--audio-format mp3",
                "--embed-metadata",
                "--embed-thumbnail",
            },
        },
        presets::preset{
            .name{"audio-low"},
            .desc{"Rip audio from URLs"},
            .flags{
                "--extract-audio",
            },
        },

        // presets related to video
        presets::preset{
            .name{"video"},
            .desc{"Extract and format video from URLs"},
            .flags{
                "-f bv[height<=1080]+ba/b[height<=1080]",
                "-S vcodec:h264,acodec:aac",
                "--merge-output-format mp4",
                "--embed-metadata",
                "--embed-thumbnail",
                "--sub-langs en.*,ja,zh.* --embed-subs",
            },
        },
        presets::preset{
            .name{"video-low"},
            .desc{"Rip video from URLs"},
            .flags{
                "-f bv[height<=720]+ba/b[height<=720]",
                "--merge-output-format mkv",
            },
        },
        presets::preset{
            .name{"video-nores"},
            .desc{"Extract and format video from URLs (no resolution specifier)"},
            .flags{
                "-S vcodec:h264,acodec:aac",
                "--merge-output-format mp4",
                "--embed-metadata",
                "--embed-thumbnail",
                "--sub-langs en.*,ja,zh.* --embed-subs",
            },
        },
        presets::preset{
            .name{"video-low-nores"},
            .desc{"Rip video from URLs (no resolution specifier)"},
            .flags{
                "--merge-output-format mkv",
            },
        },

        // miscellaneous presets
        presets::preset{
            .name{"thumbnail"},
            .desc{"Extract thumbnail from URLs"},
            .flags{
                "--skip-download",
                "--write-thumbnail",
            },
        },
    }};

    // first, grab user args
    user_args::user_args user_args;
    try
    {
        user_args = user_args::parse(preset_list, argc, argv);
    }
    catch (const std::invalid_argument &err)
    {
        std::cerr << err.what() << "\n";
        return expected_err;
    }

    // then, redirect the urls
    for (auto &url : user_args.urls)
    {
        try
        {
            url = url_parsing::redirect_url(url);
        }
        catch (const std::out_of_range &err)
        {
            std::cerr << err.what() << "\n";
            return expected_err;
        }
        catch (const std::invalid_argument &err)
        {
            std::cerr << err.what() << " - skipping redirect...\n";
            continue;
        }
        catch (const std::runtime_error &err)
        {
            std::cerr << "[ERR] " << err.what() << "\n";
            return unexpected_err;
        }
    }

    // finally, call downloader on each url
    for (const auto &url : user_args.urls)
    {
        try
        {
            download::download(user_args.selected_preset, url);
        }
        catch (const std::runtime_error &err)
        {
            std::cerr << err.what() << "\n";
            return expected_err;
        }
    }

    return 0;
}
