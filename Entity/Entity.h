#ifdef ENTITY_EXPORTS
#define ENTITY_API __declspec(dllexport)
#else
#define ENTITY_API __declspec(dllimport)
#endif

