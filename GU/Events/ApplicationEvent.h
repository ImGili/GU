/*
 * @Author: ImGili
 * @Description: 
 */
#include"Event.h"
namespace GU
{
    class GU_API WindowsClosedEvnet : public Event
    {
    public:
        GU_EVENT_GET_TYPE_OVERRIDE(WindowsCloseEvent)
    };
} 
