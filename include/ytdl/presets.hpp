#ifndef YTDL_YTDL_PRESETS_HPP
#define YTDL_YTDL_PRESETS_HPP

#include <string>
#include <vector>
#include <string_view>

namespace ytdl::presets {

struct preset {
    std::string name;
    std::string desc;
    std::vector<std::string> flags;
};

class supported_presets {
   private:
    std::vector<preset> preset_list;

   public:
    explicit supported_presets(const std::vector<preset>&);
    preset& get_preset(const std::string_view&);
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
