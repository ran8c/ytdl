cmake_minimum_required(VERSION 3.12)

project(ytdl LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
function(ytdl_set_properties selected_target)
  set_target_properties(
    ${selected_target}
    PROPERTIES CXX_STANDARD 20
               CXX_STANDARD_REQUIRED ON
               CXX_EXTENSIONS OFF)
endfunction()

find_package(Boost REQUIRED CONFIG COMPONENTS format process url)

add_subdirectory(src)

add_executable(ytdl "src/ytdl.cpp")
ytdl_set_properties(ytdl)
target_link_libraries(
  ytdl PRIVATE
  ytdl::env
  ytdl::presets)