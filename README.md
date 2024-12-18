# ytdl

A command-line interface for [yt-dlp](https://github.com/yt-dlp/yt-dlp).

## Dependencies

- [Clang](https://clang.llvm.org)
  - [clang-tidy](https://clang.llvm.org/extra/clang-tidy)
  - [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
- [CMake](https://cmake.org)
- [cmake-format](https://github.com/cheshirekow/cmake_format)
- [vcpkg](https://vcpkg.io)

## Compilation

```bash
cmake --prefix debug
cmake --build build/debug > build.log
ln -s build/debug/compile_commands.json .
./build/debug/ytdl

cmake --preset debug -DYTDL_LINT=true
cmake --build build/debug

cmake --prefix release
cmake --build build/release
cmake --install build/release --prefix ~/.local
ytdl
```
