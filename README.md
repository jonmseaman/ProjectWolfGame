# ProjectWolfGame
A prototype for a terminal-based RPG.

## Tools
* CMake 4.4 or newer
* A C++23 compiler

## How to Build
```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build
```

## Building with `import std`

The sources use `import std;` in place of standard library headers when the
toolchain can support it, and fall back to including headers when it cannot.
Both configurations are expected to build and pass the tests.

Turning it on needs all three of:

* A generator that can scan module dependencies -- Ninja 1.11+ or Visual Studio
* A standard library that ships module sources, and a compiler that ships
  `clang-scan-deps`. Apple's clang ships **neither**, so the default macOS
  build uses headers.

`import std` is still behind an experimental gate in CMake, and the gate value
is tied to a CMake release. `CMakeLists.txt` carries the value CMake 4.4
expects; on a newer CMake the gate does not open and the build falls back to
headers until that value is updated.

With Homebrew LLVM on macOS:

```bash
LLVM=$(brew --prefix llvm)
cmake -S . -B build-modules -G Ninja \
  -DCMAKE_CXX_COMPILER=$LLVM/bin/clang++ \
  -DCMAKE_CXX_STDLIB_MODULES_JSON=$LLVM/lib/c++/libc++.modules.json \
  -DCMAKE_CXX_FLAGS="-nostdinc++ -isystem $LLVM/include/c++/v1" \
  -DCMAKE_SHARED_LINKER_FLAGS="-L$LLVM/lib/c++ -Wl,-rpath,$LLVM/lib/c++" \
  -DCMAKE_EXE_LINKER_FLAGS="-L$LLVM/lib/c++ -Wl,-rpath,$LLVM/lib/c++"
cmake --build build-modules
ctest --test-dir build-modules
```

Configuring prints which mode is in use:

```
-- import std: ON
```

`CMAKE_CXX_STDLIB_MODULES_JSON` is needed because CMake locates the module
metadata by asking the compiler, without the flags that would point it at
Homebrew's libc++. `-DPWG_IMPORT_STD=ON` forces the mode on and fails the
configure step with an explanation if the toolchain cannot provide it.

## Controls

* `12345` - Menu access
* `wasdqe` - Movement
* `i` - Inventory
* `Space` - Attack
* `t` - Change target
* `Enter` - End turn
* `S` - Save
* `L` - Load

## Screenshot
![Screenshot of UI](Documentation/ProjectWolfGame_UI.png)
