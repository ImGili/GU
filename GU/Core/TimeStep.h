/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
namespace GU
{
    class GU_API TimeStep
    {
    public:
        TimeStep(float time = 0.0f)
            :m_Time(time)
        {}

        operator float() const 
        {
            return m_Time;
        }
    private:
        float m_Time;
    };
}
