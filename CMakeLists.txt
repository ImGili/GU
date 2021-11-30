cmake_minimum_required(VERSION 3.0)
project(Gu)

option(GU_BUILD_EXAMPLES "Build GUEngine Examples" ON)

option(GU_BUILD_SHARED_LIBRARY ON)

option(GU_DEBUG_ENABLE ON)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(vendor/glfw)

add_subdirectory(vendor/spdlog)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(vendor/assimp)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /source-charset:utf-8 /execution-charset:gbk /std:c++17")
else()
    if(APPLE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wno-parentheses  -std=c++17")
        message("Apple")
    elseif(WIN32)
        message("WIN32")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wno-parenthese -fexec-charset=GBK  -std=c++17")
    elseif(UNIX AND NOT APPLE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Wpedantic  -std=c++17")
        message("Linux")        
    endif()
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()


# configure_file (
#     "${PROJECT_SOURCE_DIR}/configuration/rw_config.h.in"
#     "${PROJECT_SOURCE_DIR}/include/rw_config.h"
# )


file(GLOB VENDORS_SOURCES           vendor/glad/src/glad.c
                                    vendor/imgui/backends/imgui_demo.cpp
                                    vendor/stb/stb_image.cpp
                                    vendor/assimp/include/
                                    )
file(GLOB PROJECT_HEADERS           GU/*.h
                                    )
file(GLOB PROJECT_SOURCES           GU/Core/*.cpp
                                    GU/Platform/GLFWPlatform/*.cpp
                                    GU/Platform/OpenGL/*.cpp
                                    GU/ImGui/*.cpp
                                    GU/Renderer/*.cpp
                                    GU/AI/*.cpp
                                    GU/Scene/*.cpp
                                    vendor/imgui/*.cpp
                                    vendor/imgui/backends/imgui_impl_opengl3.cpp
                                    vendor/imgui/backends/imgui_impl_glfw.cpp
                                    vendor/RVO2/src/*.cpp
                                    )

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_definitions(-DGU_ENABLE_DEBUG)
add_definitions(-DGLAD_GLAPI_EXPORT)

add_library(${PROJECT_NAME} SHARED
                                ${PROJECT_SOURCES} 
                                ${PROJECT_HEADERS}
                                ${VENDORS_SOURCES}
            )
if(MSVC)
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
                COMPILE_FLAGS "-DGU_PLATFORM_WINDOWS -DGU_BUILD_DLL")
add_definitions(-DASSIMP_BUILD_DLL_EXPORT)
elseif(APPLE)
add_definitions(-DGU_PLATFORM_MACOS)
endif()

if(GU_DEBUG_ENABLE)
    add_definitions(-DGU_DEBUG_ENABLE)
endif()




target_include_directories(${PROJECT_NAME} PUBLIC
                                GU/
                                vendor/glad/include/
                                vendor/glfw/include/
                                vendor/glm/
                                vendor/imgui/
                                vendor/spdlog/include/
                                vendor/RVO2/src
                                vendor/stb
                                vendor/entt
             )

target_link_libraries(${PROJECT_NAME} PUBLIC
                                glfw
                                ${GLFW_LIBRARIES} 
                                ${GLAD_LIBRARIES}
                                spdlog::spdlog
                                assimp
                      )
# set_target_properties(${PROJECT_NAME} PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

if (GU_BUILD_EXAMPLES)
    message("GU BUILD EXAMPLE")
    add_subdirectory(examples/quickstart)
    add_subdirectory(examples/aiquickstart)
endif()

