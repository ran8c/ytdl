#ifndef YTDL_YTDL_PRESETS_HPP
#define YTDL_YTDL_PRESETS_HPP

#include <string>
#include <string_view>
#include <vector>

namespace ytdl::presets
{

/**
 * A configured preset for the downloader.
 */
struct preset
{
    std::string name;
    std::string desc;
    std::vector<std::string> flags;
};

/**
 * @brief Class storing a list of supported presets.
 */
class supported_presets
{
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

}  // namespace ytdl::presets

#endif
