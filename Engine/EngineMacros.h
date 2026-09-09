#ifndef ENGINE_MACROS_H
#define ENGINE_MACROS_H

// Macros are not exported by modules, so ENGINE_API lives in a header that is
// included textually, in the global module fragment of Engine's module units.

#if defined(_MSC_VER) || defined(__MINGW32__)
#  ifdef ENGINE_EXPORTS
#    define ENGINE_API __declspec(dllexport)
#  else
#    define ENGINE_API __declspec(dllimport)
#  endif
#else
#  define ENGINE_API
#endif

#endif // ENGINE_MACROS_H
