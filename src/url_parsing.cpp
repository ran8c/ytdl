#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>

#include "ytdl/url_parsing.hpp"

#include <ada.h>
#include <ada/url_search_params.h>
#include <fmt/format.h>

namespace url_parsing = ytdl::url_parsing;

namespace
{

/**
 * Validates if a given path name is a valid short URL token.
 * @param `std::string_view`: the path name to validate.
 * @return true if the path is a valid token.
 * @return false if the path is not a valid token.
 */
bool validate_short_path(const std::string_view& pathname)
{
    std::vector<std::string> valid_tokens {
        // regular url
        "watch",
        // channel url
        "channel",
        "@",
        // playlist url
        "playlist",
        // shorts
        "shorts",
    };

    for (const auto& token : valid_tokens) {
        if (pathname.starts_with(token)) {
            return true;
        }
    }

    return false;
}

}  // namespace

std::string url_parsing::redirect_url(const std::string_view& incoming_url)
{
    if (incoming_url.empty()) {
        throw std::invalid_argument("blank url given");
    }

    auto url = ada::parse(incoming_url);
    if (!url) {
        const std::string msg = fmt::format("failed to parse url: {}", incoming_url);
        throw std::invalid_argument(msg);
    }

    // ada complies with the url standard afaik, so this is useful:
    // https://developer.mozilla.org/en-US/docs/Web/API/URL

    url->set_protocol("https");
    url->set_host("youtube.com");

    /**
     * Rebuilds the active URL query to follow a regular URL.
     * @param `std::string_view`: the id to transform into a valid query.
     */
    auto rebuild_query = [&url](const std::string_view& url_id)
    {
        url->set_pathname("/watch");
        url->set_search(fmt::format("v={}", url_id));
    };

    // handle dirty urls
    ada::url_search_params queries {url->get_search()};
    if (queries.has("v")) {
        rebuild_query(queries.get("v").value());
    }

    // handle short video urls...
    const std::string_view found_path {url->get_pathname().substr(1)};
    // ...but only if we didn't confuse it with something else
    if (!validate_short_path(found_path)) {
        rebuild_query(std::string(found_path));
    }

    // this shouldn't happen, but pass the error up if it does
    if (!url->validate()) {
        const std::string msg = fmt::format("url object is invalid: {}", url->to_string());
        throw std::runtime_error(msg);
    }

    // clone here is intentional, i don't like changing parameters in-place
    return std::string(url->get_href());
}
