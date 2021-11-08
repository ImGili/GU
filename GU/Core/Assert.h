#include"Core.h"
#include"Log.h"
#define GU_ASSERT(checked, string) { if(!(checked)) {GU_ERROR(string); GU_DEBUGBREAK();} }