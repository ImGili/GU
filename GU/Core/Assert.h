#include"Core.h"
#include"Log.h"
#define GU_ASSERT(checked, ...) { if(!(checked)) { GU_ERROR(__VA_ARGS__); GU_DEBUGBREAK(); } }