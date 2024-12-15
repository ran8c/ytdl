#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "ytdl/url_parsing.hpp"

namespace url_parsing = ytdl::url_parsing;

TEST_CASE("No URL")
{
    CHECK_THROWS(url_parsing::redirect_url(""));
}

TEST_CASE("YouTube URLs")
{
    // standard URLs
    CHECK(url_parsing::redirect_url("https://www.youtube.com/watch?v=01rXk7iRDwg") == "https://youtube.com/watch?v=01rXk7iRDwg");
    // shortened URLs
    CHECK(url_parsing::redirect_url("https://youtu.be/01rXk7iRDwg") == "https://youtube.com/watch?v=01rXk7iRDwg");
    // shorts URLs
    CHECK(url_parsing::redirect_url("https://www.youtube.com/shorts/01rXk7iRDwg") == "https://youtube.com/shorts/01rXk7iRDwg");
    // dirty URLs
    CHECK(url_parsing::redirect_url("https://www.youtube.com/watch?app=desktop&v=txOXb9IYTVg&list=PL_JpBVQzSLRe1EjKu_Me8wKegvoc1YLsD&index=1") == "https://youtube.com/watch?v=txOXb9IYTVg");
    // channel URLs
    CHECK(url_parsing::redirect_url("https://www.youtube.com/@realwebdrivertorso") == "https://youtube.com/@realwebdrivertorso");
    // playlist URLs
    CHECK(url_parsing::redirect_url("https://www.youtube.com/playlist?list=PL_JpBVQzSLRe1EjKu_Me8wKegvoc1YLsD") == "https://youtube.com/playlist?list=PL_JpBVQzSLRe1EjKu_Me8wKegvoc1YLsD");
}

TEST_CASE("Invidious URLs")
{
    // standard URLs
    CHECK(url_parsing::redirect_url("https://inv.nadeko.net/watch?v=01rXk7iRDwg") == "https://youtube.com/watch?v=01rXk7iRDwg");
    // channel URLs
    CHECK(url_parsing::redirect_url("https://inv.nadeko.net/channel/UCsLiV4WJfkTEHH0b9PmRklw") == "https://youtube.com/channel/UCsLiV4WJfkTEHH0b9PmRklw");
    // playlist URLs
    CHECK(url_parsing::redirect_url("https://inv.nadeko.net/playlist?list=PL_JpBVQzSLRe1EjKu_Me8wKegvoc1YLsD") == "https://youtube.com/playlist?list=PL_JpBVQzSLRe1EjKu_Me8wKegvoc1YLsD");
}
