/*
 * @Author: ImGili
 * @Description: 
 */
#include<glm/glm.hpp>
#include<RVO.h>
#define RVO_VEC2_TO_GLM_VEC2(arg) glm::vec2(arg.x(), arg.y()) 
#define GLM_VEC2_TO_RVO_VEC2(arg) RVO::Vector2(arg.x, arg.y) 

#define GU_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
