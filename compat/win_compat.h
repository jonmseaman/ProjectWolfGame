// Force-included on non-MSVC to neutralize Windows DLL export macros.
// __declspec(dllexport/dllimport) are MSVC/MinGW-only; on macOS/Linux they
// map to nothing so the project compiles without source changes.
#if !defined(_MSC_VER)
#  define __declspec(x)
#endif
