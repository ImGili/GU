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
    s_Log->set_pattern("%^[GU][%D %T]: %v%$");
}
std::shared_ptr<spdlog::logger> Log::Get()
{
    return s_Log;
}