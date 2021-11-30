cmake_minimum_required(VERSION 3.0)
project(quickstart)

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


add_executable(${PROJECT_NAME} 
                main.cpp ExampleLayer.h ExampleLayer.cpp EditorLayer.h EditorLayer.cpp Example3DLayer.h Example3DLayer.cpp)


target_link_libraries(${PROJECT_NAME} 
    PUBLIC
            Gu
)

if(MSVC)
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
                COMPILE_FLAGS "-DGU_PLATFORM_WINDOWS")
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/build/Debug/Gud.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>/)
endif()

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets/)
