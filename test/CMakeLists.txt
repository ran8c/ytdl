find_package(doctest REQUIRED)

add_executable(ytdl_test "ytdl_test.cpp")
ytdl_set_properties(ytdl_test)
target_link_libraries(ytdl_test PRIVATE doctest::doctest ytdl::url_parsing)

add_custom_command(
  TARGET ytdl_test
  POST_BUILD
  COMMAND $<TARGET_FILE:ytdl_test>
)
