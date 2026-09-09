# ProjectWolfGame
A prototype for a terminal-based RPG.

## Tools

* CMake 4.3.1 or newer
* Ninja 1.11 or newer, or Visual Studio
* A C++23 toolchain that can provide `import std`

The sources use `import std;` and have no header fallback, so the standard
library has to be available as a module. That needs three things together:

* **A generator that can scan module dependencies.** Ninja or Visual Studio.
  The Makefile generators cannot, so plain `cmake -S . -B build` will not work.
* **A standard library shipping module sources** -- a `std.cppm` and a
  `libc++.modules.json`, or the libstdc++ equivalent.
* **A compiler shipping `clang-scan-deps`**, which is how CMake works out the
  import graph.

Apple's clang ships the module sources (in `/usr/share/libc++/v1`) but **not**
`clang-scan-deps`, so it cannot build this project. Use an upstream LLVM.
CMake fails at configure time with an explanation if any piece is missing.

## How to Build

On macOS with Homebrew LLVM:

```bash
brew install llvm ninja
cmake -S . -B build -G Ninja -DCMAKE_CXX_COMPILER=$(brew --prefix llvm)/bin/clang++
cmake --build build
ctest --test-dir build
```

Elsewhere, any Ninja plus a module-capable compiler will do:

```bash
cmake -S . -B build -G Ninja -DCMAKE_CXX_COMPILER=clang++
cmake --build build
ctest --test-dir build
```

Configuring reports what it found:

```
-- import std: linking libc++ from /opt/homebrew/opt/llvm/lib/c++
-- import std: using /opt/homebrew/opt/llvm/lib/c++/libc++.modules.json
```

Two things are handled for you, and both can be overridden on the command line:

* CMake locates the module metadata by running the compiler with
  `-print-file-name`, without any of this project's flags, so it does not find
  a libc++ that is not the compiler's default. The build looks next to the
  compiler instead. Override with `-DCMAKE_CXX_STDLIB_MODULES_JSON=...`.
* The `std` module is built from the compiler's own libc++, but the linker
  reaches for the platform's by default -- on macOS that silently pairs
  Homebrew's headers with Apple's `/usr/lib/libc++.1.dylib`. The build adds the
  matching `-L` and `-rpath` so both come from one place.

`import std` is still behind an experimental gate in CMake, and the gate value
is tied to a CMake release. `CMakeLists.txt` carries the value CMake **4.4**
expects; on a CMake that wants a different one the gate stays shut and
configuring fails, so that value has to be kept current.

## Headers

Project headers still include the standard headers they need, rather than
relying on `import std` from whatever includes them: a header has to be
self-contained, and keeping them textual leaves the door open to turning the
project's own headers into modules later.

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
