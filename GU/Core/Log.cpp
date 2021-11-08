/*
 * @Author: ImGili
 * @Description: 
 */
#include"Log.h"
#include"spdlog/formatter.h"

using namespace GU;

std::shared_ptr<spdlog::logger> Log::s_Log;
void Log::Init()
{
    s_Log = spdlog::stderr_color_mt("GU_Log");
    #ifdef GU_ENABLE_DEBUG
    s_Log->set_pattern("%^[GU][%D %T]%@: %v%$");
    #else
    s_Log->set_pattern("%^[GU][%D %T]: %v%$");
    #endif
}
std::shared_ptr<spdlog::logger> Log::Get()
{
    return s_Log;
}