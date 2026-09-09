#ifndef SAVABLE_MACROS_H
#define SAVABLE_MACROS_H

// Macros are not exported by modules, so the ones that Savable's API relies on
// live in this header and are included textually by whoever needs them --
// including Savable's own module interface unit, in its global module fragment.

#if defined(_MSC_VER) || defined(__MINGW32__)
#  ifdef SAVABLE_EXPORTS
#    define SAVABLE_API __declspec(dllexport)
#  else
#    define SAVABLE_API __declspec(dllimport)
#  endif
#else
#  define SAVABLE_API
#endif

#define SAVE(var) Savable::save( #var, var )
#define LOAD(var) Savable::load( #var, var )

/** Makes it easier to declare necessary savable functions. */
#define SAVABLE void save() override; void load() override
#define SAVABLE_CLEAR void save() override; void load() override; \
                      void clearSavable() override

#endif // SAVABLE_MACROS_H
