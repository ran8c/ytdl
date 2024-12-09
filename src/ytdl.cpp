#include "ytdl/env.hpp"
#include "ytdl/presets.hpp"
#include "ytdl/user_args.hpp"

#include <iostream>

using namespace ytdl;

int main(int argc, char* argv[]) {
    // get supported environment variables
    env::current_env_vars ENV_VARS{{"DEBUG", "VERBOSE"}};

    // create list of supported presets
    presets::supported_presets PRESET_LIST{{
        // presets related to audio
        preset{
            .name{"audio"},
            .desc{"Extract and format audio from URLs"},
            .flags{
                "--extract-audio",
                "--audio-format mp3",
                "--embed-metadata",
                "--embed-thumbnail",
            },
        },
        preset{
            .name{"audio-low"},
            .desc{"Rip audio from URLs"},
            .flags{
                "--extract-audio",
            },
        },

        // presets related to video
        preset{
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
        preset{
            .name{"video-low"},
            .desc{"Rip video from URLs"},
            .flags{
                "-f bv[height<=720]+ba/b[height<=720]",
                "--merge-output-format mkv",
            },
        },
        preset{
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
        preset{
            .name{"video-low-nores"},
            .desc{"Rip video from URLs (no resolution specifier)"},
            .flags{
                "--merge-output-format mkv",
            },
        },

        // miscellaneous presets
        preset{
            .name{"thumbnail"},
            .desc{"Extract thumbnail from URLs"},
            .flags{
                "--skip-download",
                "--write-thumbnail",
            },
        },
    }};

    // currently, just print out debugging information
    ENV_VARS.print();
    PRESET_LIST.print();

    user_args::user_args user_args;
    try {
        user_args = user_args::parse(PRESET_LIST, argc, argv);
    } catch (const std::invalid_argument& err) {
        std::cerr << err.what() << "\n";
        return 1;
    }
    user_args.print();

    return 0;
}
