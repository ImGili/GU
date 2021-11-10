/*
 * @Author: ImGili
 * @Description: 
 */
#include"Platform/OpenGL/OpenGLShader.h"
#include"Core/Log.h"
#include<glad/glad.h>
#include<fstream>
#include<sstream>
using namespace GU;
OpenGLShader::OpenGLShader(const char* name, const char* vertexPath, const char* fragmentPath, const char* geometryPath)
    : m_Name(name)
{
    // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();		
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();			
            // if geometry shader path is present, also load a geometry shader
            if(geometryPath != nullptr)
            {
                gShaderFile.open(geometryPath);
                std::stringstream gShaderStream;
                gShaderStream << gShaderFile.rdbuf();
                gShaderFile.close();
                geometryCode = gShaderStream.str();
            }
        }
        catch (std::ifstream::failure& e)
        {
            GU_ERROR("Shader file can't read succesfully! ERROR: {0}", e.what());
        }
        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        CheckCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        CheckCompileErrors(fragment, "FRAGMENT");

        unsigned int geometry;
        if(geometryPath != nullptr)
        {
            const char * gShaderCode = geometryCode.c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, NULL);
            glCompileShader(geometry);
            CheckCompileErrors(geometry, "GEOMETRY");
        }

        // shader Program
        m_RenderID = glCreateProgram();
        glAttachShader(m_RenderID, vertex);
        glAttachShader(m_RenderID, fragment);
        if(geometryPath != nullptr)
            glAttachShader(m_RenderID, geometry);
        glLinkProgram(m_RenderID);
        CheckCompileErrors(m_RenderID, "PROGRAM");

        unsigned int uniformBlockIndex = glGetUniformBlockIndex(m_RenderID, "CameraMatrices");
        if (uniformBlockIndex != GL_INVALID_INDEX)
        {
            glUniformBlockBinding(m_RenderID, uniformBlockIndex, 0);
        }
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (geometryPath != nullptr)
        {
            glDeleteShader(geometry);
        }
        
}

void OpenGLShader::CheckCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            GU_ERROR("{0} Shader complie error, error code: {1}", type, infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            GU_ERROR("{0} Shader complie error, error code: {1}", type, infoLog);
        }
    }
}

void OpenGLShader::Bind()
{
    glUseProgram(m_RenderID);
}

void OpenGLShader::Unbind()
{
    glUseProgram(0);
}