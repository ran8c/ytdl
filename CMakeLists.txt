cmake_minimum_required(VERSION 3.12)

project(ytdl LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
function(ytdl_set_properties selected_target)
    set_target_properties(
        ${selected_target}
        PROPERTIES CXX_STANDARD 20
                   CXX_STANDARD_REQUIRED ON
                   CXX_EXTENSIONS OFF
    )
    if(YTDL_LINT)
        message("-- ytdl: linting enabled on target ${selected_target}")
        set_property(
            TARGET ${selected_target}
            APPEND
            PROPERTY CXX_CLANG_TIDY "clang-tidy;-p;${CMAKE_BINARY_DIR}"
        )
    endif()
endfunction()

find_package(fmt REQUIRED)
find_package(ada REQUIRED)
find_package(Boost REQUIRED COMPONENTS process)

add_subdirectory(src)

if(YTDL_BUILD_TESTS)
    message("-- ytdl: tests enabled")
    add_subdirectory(test)
endif()

add_executable(ytdl "src/ytdl.cpp")
ytdl_set_properties(ytdl)
target_link_libraries(ytdl PRIVATE ytdl::ytdl)

include(GNUInstallDirs)
install(TARGETS ytdl)
