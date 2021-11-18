/*
 * @Author: ImGili
 * @Description: 
 */
#include"AI/AgentSimulator.h"
#include"Renderer/Renderer2D.h"
#include"Core/Base.h"
#include"Core/Log.h"
using namespace GU;

///////////////////////////////////
///// Agent////////////////////////
///////////////////////////////////
void Agent::Draw()
{
	Renderer2D::DrawQuad(Position, glm::vec4(Color.r,Color.g, Color.b, 1.0));
}

float Agent::DistanceGoal()
{
	glm::vec2 tmp = Goals[CurrentNode] - Position;
	return (tmp.x + tmp.y);
}
void Agent::AddCurrentNode()
{
	if (CurrentNode >= Goals.size()-1)
	{
		return;
	}
	CurrentNode++;
}
const glm::vec2& Agent::GetCurrentGoal() const
{
	return Goals[CurrentNode];
}

///////////////////////////////////
///// AgentSimulator///////////////
///////////////////////////////////

AgentSimulator::AgentSimulator()
	: m_Sim(std::make_unique<RVO::RVOSimulator>()), AgentPtr(0)
{
    /* Specify the global time step of the simulation. */
	m_Sim->setTimeStep(0.25f);

	/* Specify the default parameters for agents that are subsequently added. */
	m_Sim->setAgentDefaults(15.0f, 10, 5.0f, 5.0f, 2.0f, 2.0f);
}

void AgentSimulator::OnUpdate()
{
	if (!IsAllAgentsReachFinalGoal())
	{
		UpdateAgents();
	}
}

void AgentSimulator::AddAgents(std::initializer_list<Agent> agents)
{
	AgentPtr = m_Agents.size();
	m_Agents.insert(m_Agents.end(), agents);
	for (size_t i = AgentPtr; i < m_Agents.size(); i++)
	{
		m_Sim->addAgent(GLM_VEC2_TO_RVO_VEC2(m_Agents[i].Position));
		UpdateAgentPerV(i);
	}
}

bool AgentSimulator::IsReachGoal(uint32_t i)
{
	
	if (i < m_Agents.size() && m_Agents[i].DistanceGoal() <= 20*20)
	{
		if (m_Agents[i].CurrentNode>(m_Agents[i].Goals.size()-1))
		{
			m_Agents[i].IsReachFinalGoals = true;
		}
		return true;
	}
	return false;
}
bool AgentSimulator::IsAllAgentsReachFinalGoal()
{
	for (size_t i = 0; i < m_Agents.size(); i++)
	{
		if (m_Agents[i].IsReachFinalGoals == false)
		{
			return false;
		}
	}
	return true;
}


void AgentSimulator::DrawAgents()
{
	for (size_t i = 0; i < m_Agents.size(); i++)
	{
		m_Agents[i].Draw();
	}
}

void AgentSimulator::UpdateAgents()
{
	m_Sim->doStep();
	for (size_t i = 0; i < m_Agents.size(); i++)
	{
		m_Agents[i].Position = RVO_VEC2_TO_GLM_VEC2(m_Sim->getAgentPosition(i));
		if (IsReachGoal(i))
		{
			m_Agents[i].AddCurrentNode();
			UpdateAgentPerV(i);
		}
	}
}

void AgentSimulator::UpdateAgentPerV(uint32_t i)
{
	RVO::Vector2 goalVector = GLM_VEC2_TO_RVO_VEC2(m_Agents[i].GetCurrentGoal()) - m_Sim->getAgentPosition(i);
	if (RVO::absSq(goalVector) > 1.0f) {
		goalVector = RVO::normalize(goalVector);
	}
	m_Sim->setAgentPrefVelocity(i, goalVector);
}