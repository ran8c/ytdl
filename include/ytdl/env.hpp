#ifndef YTDL_YTDL_ENV_HPP
#define YTDL_YTDL_ENV_HPP

#include <string>
#include <vector>

namespace ytdl::env {

/**
 * @brief A class representing a single environment variable
 */
class env_var {
   private:
    /**
     * @brief The ALL_CAPS name of the environment variable
     */
    std::string name;

    /**
     * @brief Whether the environment variable is set
     */
    bool status{false};

   public:
    /**
     * @brief Construct an `env_var` object by parsing an environment variable
     * @param The ALL_CAPS name of the environment variable to parse
     */
    explicit env_var(const std::string_view&);

    /**
     * @brief Get the ALL_CAPS name of the environment variable (`env_var.name`)
     */
    std::string_view get_name();

    /**
     * @brief Get the status of the environment variable (`env_var.status`)
     * @return `true` if the environment variable was set at startup
     * @return `false` if the environment variable was not set at startup
     */
    [[nodiscard]] bool get_status() const;
};

/**
 * @brief A class representing a list of environment variables
 */
class current_env_vars {
   private:
    /**
     * @brief The list of stored environment variables
     */
    std::vector<env_var> vars;

   public:
    /**
     * @brief Construct a list of environment variables
     * @param A list of environment variable names to store
     */
    explicit current_env_vars(const std::vector<std::string>&);

    /**
     * @brief Get a stored environment variable
     * @throw `std::invalid_argument` if passed variable isn't present in the stored list
     */
    env_var& get(const std::string_view&);

    /**
     * @brief Prints all stored environment variables and their status
     */
    void print();
};

/**
 * @brief Supported environment variables for `ytdl`
 */
// NOLINTNEXTLINE: i am okay with `std::terminate` if allocating this fails
static current_env_vars ENV_VARS{{"DEBUG", "VERBOSE"}};

}  // namespace ytdl::env

#endif