#include "ytdl/env.hpp"

#include <iostream>

#include <boost/format.hpp>
#include <boost/process.hpp>

using namespace ytdl::env;

/**
 * Uses Boost::Process v1 to get environment variable from current process.
 *
 * TODO: is there a way to do this with v2? v1 is deprecated...
 */
env_var::env_var(const std::string_view& name) : name(name) {
    auto current_env = boost::this_process::environment();
    if (current_env.find(this->name) != current_env.end()) {
        this->status = true;
    }
}

/**
 * Getter for `env_var.name`.
 */
std::string_view env_var::get_name() { return this->name; }

/**
 * Getter for `env_var.status`.
 */
bool env_var::get_status() const { return this->status; }

/**
 * Constructor for `current_env_vars`.
 */
current_env_vars::current_env_vars(const std::vector<std::string>& vars) {
    for (const auto& var : vars) {
        // `env_var` has a `std::string` constructor, so compiler implicitly makes the `env_var` before appending.
        this->vars.emplace_back(var);
    }
}

/**
 * Getter for `current_env_vars`.
 *
 * @throw `std::invalid_argument` if `name` is not in current instance.
 */
env_var& current_env_vars::get(const std::string_view& name) {
    // i could use `std::find_if()`, but it feels "too academic" compared to a early-returning range loop
    for (auto& var : this->vars) {
        if (var.get_name() == name) {
            return var;
        }
    }
    // extra formatting to add the invalid parameter to the error message
    const auto exception{boost::format("\"%1%\" not supported") % name};
    throw std::invalid_argument(exception.str());
}

/**
 * Debug print contents of `current_env_vars`.
 */
void current_env_vars::print() {
    for (auto& var : this->vars) {
        // `std::clog` is `std::cerr` with string buffering
        // using one over the other is about intentionality: `std::clog` is neither an error or standard output
        std::clog << boost::format("[DEBUG] %s=%b\n") % var.get_name() % var.get_status();
    }
}
