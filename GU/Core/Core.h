#ifdef GU_PLATFORM_WINDOWS
	#ifdef GU_BUILD_DLL
		#define GU_API __declspec(dllexport)
	#else
		#define GU_API __declspec(dllimport)
	#endif
#else
    #define GU_API
#endif

#ifdef GU_ENABLE_DEBUG
#ifdef GU_PLATFORM_WINDOWS
	#define GU_DEBUGBREAK() __debugbreak()
#else
	#include <signal.h>
	#define GU_DEBUGBREAK() raise(SIGTRAP);
#endif
#else
	#define GU_DEBUGBREAK()
#endif

// #ifdef GU_DEBUG_ENABLE
	
// #else
// 	#define GU_DEBUGBREAK()
// #endif
