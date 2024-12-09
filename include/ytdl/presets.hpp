#ifndef YTDL_YTDL_PRESETS_HPP
#define YTDL_YTDL_PRESETS_HPP

#include <string>
#include <vector>
#include <string_view>

namespace ytdl::presets {

/**
 * A configured preset for the downloader.
 */
struct preset {
    std::string name;
    std::string desc;
    std::vector<std::string> flags;
};

/**
 * @brief Class storing a list of supported presets.
 */
class supported_presets {
   private:
    /**
     * The internal set of supported presets.
     */
    std::vector<preset> preset_list;

   public:
    /**
     * @brief Store a list of presets.
     * @param `std::vector<preset>&`: the list of presets to store.
     */
    explicit supported_presets(const std::vector<preset>&);

    /**
     * @brief Get a stored preset.
     * @param `std::string_view&`: the name of a preset to get.
     * @throw `std::invalid_argument` if no preset with given name was found.
     */
    preset& get_preset(const std::string_view&);

    /**
     * @brief Print out the list of supported presets.
     *
     * This is intended for debugging.
     */
    void print();
};

static supported_presets PRESET_LIST{{
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

    preset{
        .name{"thumbnail"},
        .desc{"Extract thumbnail from URLs"},
        .flags{
            "--skip-download",
            "--write-thumbnail",
        },
    },
}};

}  // namespace ytdl::presets

#endif
