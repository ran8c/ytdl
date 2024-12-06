# ytdl

A command-line interface for [yt-dlp](https://github.com/yt-dlp/yt-dlp).

## Dependencies

- [Clang](https://clang.llvm.org)
- [CMake](https://cmake.org)
- [vcpkg](https://vcpkg.io)

## Compilation

```bash
cmake --prefix debug
cmake --build build/debug
ln -s build/debug/compile_commands.json .
./build/debug/ytdl

cmake --prefix release
cmake --build build/release
cmake --install build/release --prefix ~/.local
ytdl
```

## Contributing

**TODO**: figure out a way to automate the checklist below

Please remember to follow this checklist before creating a merge request:

- [ ] Reorganize headers into the following order:
```cpp
// corresponding header
#include "abcd.hpp"

// standard libraries
#include <filesystem>

// third-party libraries
#include <boost/process.hpp>

// namespaces
using fs = std::filesystem;
using b::t_process = boost::this_process
```
- [ ] Format all `hpp` & `cpp` files with [`clang-format`](https://clang.llvm.org/docs/ClangFormat.html)
- [ ] Lint all `hpp` & `cpp` files with [`clang-tidy`](https://clang.llvm.org/extra/clang-tidy) and [`iwyu`](https://include-what-you-use.org)
- [ ] Make sure the project still compiles successfully
- [ ] If applicable, check for memory errors/leaks with [`valgrind`](https://valgrind.org), or [sanitizers](https://github.com/google/sanitizers)
    - Recommended sanitizers: [Address](https://github.com/google/sanitizers/wiki/AddressSanitizer), [Leak](https://github.com/google/sanitizers/wiki/AddressSanitizerLeakSanitizer), [Memory](https://github.com/google/sanitizers/wiki/MemorySanitizer), [Undefined Behavior](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html)
