# ytdl

A command-line interface for [yt-dlp](https://github.com/yt-dlp/yt-dlp).

## Dependencies

- [Clang](https://clang.llvm.org)
- [CMake](https://cmake.org)
- [vcpkg](https://vcpkg.io)

## Compilation

```bash
cmake --prefix debug
cmake --build build/debug > build.log
ln -s build/debug/compile_commands.json .
./build/debug/ytdl

cmake --prefix release
cmake --build build/release
cmake --install build/release --prefix ~/.local
ytdl
```
