/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include<chrono>
#include"Core/Log.h"
#include"Core/Core.h"
#include<string>
#include<fstream>
#include<sstream>
namespace GU
{
    struct ProfileResult{
        std::string Name;
        long long Start, End;
    };

    class Instrumentor
    {
    public:
        Instrumentor() = default;

        Instrumentor(Instrumentor& other) = delete;
        Instrumentor(const Instrumentor& other) = delete;

        void WriteProfile(const ProfileResult& result)
        {
            m_OutputStream << "{";
			m_OutputStream << "\"cat\":\"function\",";
			m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
			m_OutputStream << "\"name\":\"" << result.Name << "\",";
			m_OutputStream << "\"ph\":\"X\",";
			m_OutputStream << "\"pid\":0,";
			m_OutputStream << "\"ts\":" << result.Start;
			m_OutputStream << "}";
			m_OutputStream.flush();
        }

        ~Instrumentor() = default;

        void BeginSession(const std::string& filepath = "result.json")
        {
            m_OutputStream.open(filepath);
            WriteHeader();
        }

        void EndSession()
        {
            WriteFooter();
            m_OutputStream.close();
        }
        
        static Instrumentor& Get()
        {
            static Instrumentor instance;
            return instance;
        }
    private:    
        std::ofstream m_OutputStream;
        void WriteHeader()
        {
            m_OutputStream<<"{\"otherData\": {},\"traceEvents\":[";
            m_OutputStream.flush();
        }
        void WriteFooter()
        {
            m_OutputStream << "]}";
			m_OutputStream.flush();
        }
    };
    class InstrumentorTimer
    {
    public:
        InstrumentorTimer(const char* name)
            : Name(name)
        {
            m_StartTimepoint = std::chrono::high_resolution_clock::now();
        }

        ~InstrumentorTimer()
        {
            auto endTimepoint = std::chrono::high_resolution_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
            GU_INFO("start timer : {0}, end time {1}", start, end);
            Instrumentor::Get().WriteProfile({Name, start, end});
        }
    private:
        const char* Name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    };
}

#define GU_POFILE_BEGIN_SESSION()   ::GU::Instrumentor::Get().BeginSession()
#define GU_POFILE_END_SESSION()     ::GU::Instrumentor::Get().EndSession()
#define GU_PROFILE_FUNCTION(name)   ::GU::InstrumentorTimer timer##name (#name)