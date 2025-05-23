

// LIBRARY_API is defined to either import or export symbols depending on whether or not the dll is being built
#ifdef LIBRARY_BUILD_DLL
   #define LIBRARY_API __declspec(dllexport)
#else
   #define LIBRARY_API __declspec(dllimport)
#endif