#include "ytdl/env.hpp"

#include <iostream>

#include <boost/format.hpp>
#include <boost/process.hpp>

using namespace ytdl::env;

env_var::env_var(const std::string_view& name) : name(name) {
    auto current_env = boost::this_process::environment();
    if (current_env.find(this->name) != current_env.end()) {
        this->status = true;
    }
}

std::string_view env_var::get_name() { return this->name; }

bool env_var::get_status() const { return this->status; }

current_env_vars::current_env_vars(const std::vector<std::string>& vars) {
    for (const auto& var : vars) {
        this->vars.emplace_back(var);
    }
}

env_var& current_env_vars::get(const std::string_view& name) {
    for (auto& var : this->vars) {
        if (var.get_name() == name) {
            return var;
        }
    }
    const auto exception{boost::format("\"%1%\" not supported") % name};
    throw std::invalid_argument(exception.str());
}

void current_env_vars::print() {
    for (auto& var : this->vars) {
        std::clog << boost::format("[DEBUG] %s=%b\n") % var.get_name() % var.get_status();
    }
}