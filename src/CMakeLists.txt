function(ytdl_add_library lib_name)
    cmake_parse_arguments(YTDL_LIB "" "" LINK ${ARGV})
    add_library(ytdl_${lib_name} ${PROJECT_SOURCE_DIR}/src/${lib_name}.cpp)
    add_library(ytdl::${lib_name} ALIAS ytdl_${lib_name})

    ytdl_set_properties(ytdl_${lib_name})
    target_include_directories(ytdl_${lib_name} PUBLIC ${PROJECT_SOURCE_DIR}/include)
    target_sources(ytdl_${lib_name} PRIVATE
        ${PROJECT_SOURCE_DIR}/include/ytdl/${lib_name}.hpp
        ${PROJECT_SOURCE_DIR}/src/${lib_name}.cpp)
    
    if(NOT "${YTDL_LIB_LINK}" STREQUAL "")
        target_link_libraries(ytdl_${lib_name} PRIVATE ${YTDL_LIB_LINK})
    endif()
endfunction()

ytdl_add_library(env LINK Boost::format Boost::process)
ytdl_add_library(presets LINK Boost::format)