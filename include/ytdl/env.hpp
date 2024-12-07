#ifndef YTDL_YTDL_ENV_HPP
#define YTDL_YTDL_ENV_HPP

#include <string>
#include <vector>

namespace ytdl::env {

/**
 * @brief Class storing a single environment variable.
 */
class env_var {
   private:
    /**
     * The environment variable as a string.
     */
    std::string name;

    /**
     * Whether the environment variable was set in the current process.
     */
    bool status{false};

   public:
    /**
     * @brief Parse an environment variable from the current environment and store it.
     * @param The name of the environment variable to parse.
     * @return A constructed `env_var` object.
     */
    explicit env_var(const std::string_view&);

    /**
     * @brief Get the name of the stored environment variable.
     */
    std::string_view get_name();

    /**
     * @brief Get the status of the stored environment variable.
     */
    [[nodiscard]] bool get_status() const;
};

/**
 * @brief Class storing a set of environment variables (`env_var`).
 */
class current_env_vars {
   private:
    /**
     * The set of environment variables (`env_var`) stored.
     */
    std::vector<env_var> vars;

   public:
    explicit current_env_vars(const std::vector<std::string>&);

    env_var& get(const std::string_view&);

    void print();
};

static current_env_vars ENV_VARS{{"DEBUG", "VERBOSE"}};

}  // namespace ytdl::env

#endif
