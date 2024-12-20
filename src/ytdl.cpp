#include <iostream>
#include <stdexcept>

#include "ytdl/env.hpp"
#include "ytdl/presets.hpp"
#include "ytdl/user_args.hpp"

namespace env = ytdl::env;
namespace presets = ytdl::presets;
namespace user_args = ytdl::user_args;

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

    // currently, just print out debugging information
    env_vars.print();
    preset_list.print();

    user_args::user_args user_args;
    try
    {
        user_args = user_args::parse(preset_list, argc, argv);
    }
    catch (const std::invalid_argument &err)
    {
        std::cerr << err.what() << "\n";
        return 1;
    }
    user_args.print();

    return 0;
}
