/*
 * @Author: ImGili
 * @Description: 
 */
#pragma once
#include"Core/Core.h"
#include<RVO.h>
#include<memory>
#include<glm/glm.hpp>
#include<vector>
#include"Core/Log.h"
namespace GU
{
    struct GU_API Agent
    {
        static const uint32_t MaxGoalsNodes = 50;
        glm::vec2 Position;
        std::vector<glm::vec2> Goals;
        glm::vec3 Color;
        uint32_t CurrentNode;
        bool IsReachFinalGoals;
        void Draw();
        Agent(const glm::vec2& position, std::initializer_list<glm::vec2> goals, const glm::vec3& color)
            : Position(position), Goals(goals), CurrentNode(0), Color(color), IsReachFinalGoals(false)
        {}

        float DistanceGoal();
        void AddCurrentNode();
        const glm::vec2& GetCurrentGoal() const;
    };
    
    class GU_API AgentSimulator
    {
    public:
        AgentSimulator();
        void OnUpdate();
        void AddAgents(std::initializer_list<Agent> agents);

        void DrawAgents();
    private:
        std::unique_ptr<RVO::RVOSimulator> m_Sim;
        std::vector<Agent> m_Agents;
    private:
        bool IsReachGoal(uint32_t i);
        bool IsAllAgentsReachFinalGoal();
        void UpdateAgents();
        void UpdateAgentPerV(uint32_t i);
        uint32_t AgentPtr = 0;
    };
}