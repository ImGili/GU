/*
 * @Author: ImGili
 * @Description: 
 */
#include"Core/Input.h"
#include"Core/Application.h"
using namespace GU;
bool Input::IsKeyPressed(const KeyCode key)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
    auto state = glfwGetKey(window, static_cast<int32_t>(key));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

glm::vec2 Input::GetMoudsePosition()
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return { (float)xpos, (float)ypos };
}

bool Input::IsMousePressed(const MouseKeyCode key)
{
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
    auto state = glfwGetMouseButton(window, static_cast<int32_t>(key));
    return state == GLFW_PRESS;
}
