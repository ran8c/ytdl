#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "ytdl/env.hpp"

#include <fmt/format.h>
#include <fmt/ostream.h>

namespace env = ytdl::env;

/**
 * Gets an environment variable from the current process.
 *
 * Calls `std::getenv()`, which is not thread safe.
 */
env::env_var::env_var(const std::string &name)
    : m_name(name)
{
    const char *current_env = std::getenv(name.c_str()); // NOLINT
    if (current_env != nullptr)
    {
        this->m_status = true;
    }
}

/**
 * Getter for `env_var.name`.
 */
std::string_view env::env_var::get_name()
{
    return this->m_name;
}

/**
 * Getter for `env_var.status`.
 */
bool env::env_var::get_status() const
{
    return this->m_status;
}

/**
 * Constructor for `current_env_vars`.
 */
env::current_env_vars::current_env_vars(const std::vector<std::string> &vars)
{
    for (const auto &var : vars)
    {
        // `env_var` has a `std::string` constructor, so compiler implicitly
        // makes the `env_var` before appending.
        this->m_vars.emplace_back(var);
    }
}

/**
 * Getter for `current_env_vars`.
 *
 * @throw `std::invalid_argument` if `name` is not in current instance.
 */
env::env_var &env::current_env_vars::get(const std::string_view &name)
{
    // i could use `std::find_if()`, but it feels "too academic" compared to a
    // early-returning range loop
    for (auto &var : this->m_vars)
    {
        if (var.get_name() == name)
        {
            return var;
        }
    }
    // extra formatting to add the invalid parameter to the error message
    const std::string exception{fmt::format(R"("{}" not supported)", name)};
    throw std::invalid_argument(exception);
}

/**
 * Debug print contents of `current_env_vars`.
 */
void env::current_env_vars::print()
{
    for (auto &var : this->m_vars)
    {
        // `std::clog` is `std::cerr` with string buffering
        // using one over the other is about intentionality: `std::clog` is
        // neither an error or standard output
        fmt::print(std::clog, "[DEBUG] {}={}\n", var.get_name(), var.get_status());
    }
}
