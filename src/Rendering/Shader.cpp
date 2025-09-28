#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader() : programID(0) {}

Shader::~Shader()
{
    if (programID)
    {
        glDeleteProgram(programID);
    }
}

bool Shader::LoadFromSource(const std::string &vertexSource, const std::string &fragmentSource)
{
    const unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    const char *source = vertexSource.c_str();
    glShaderSource(vertex, 1, &source, nullptr);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    const unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    source = fragmentSource.c_str();
    glShaderSource(fragment, 1, &source, nullptr);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    programID = glCreateProgram();
    glAttachShader(programID, vertex);
    glAttachShader(programID, fragment);
    glLinkProgram(programID);
    CheckCompileErrors(programID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}

bool Shader::LoadFromFiles(const std::string &vertexPath, const std::string &fragmentPath)
{
    std::string vertexSource, fragmentSource;
    std::ifstream vShaderFile, fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexSource = vShaderStream.str();
        fragmentSource = fShaderStream.str();
    }
    catch (std::ifstream::failure &e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        return false;
    }

    return LoadFromSource(vertexSource, fragmentSource);
}

void Shader::Use() const
{
    glUseProgram(programID);
}

void Shader::CheckCompileErrors(const unsigned int shader, const std::string &type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

void Shader::SetBool(const std::string &name, const bool value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), static_cast<int>(value));
}

void Shader::SetInt(const std::string &name, const int value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, const float value) const
{
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::SetVec2(const std::string &name, const float x, const float y) const
{
    glUniform2f(glGetUniformLocation(programID, name.c_str()), x, y);
}

void Shader::SetVec3(const std::string &name, const float x, const float y, const float z) const
{
    glUniform3f(glGetUniformLocation(programID, name.c_str()), x, y, z);
}

void Shader::SetVec4(const std::string &name, const float x, const float y, const float z, const float w) const
{
    glUniform4f(glGetUniformLocation(programID, name.c_str()), x, y, z, w);
}

void Shader::SetIntArray(const std::string &name, const int *values, const uint32_t count) const
{
    glUniform1iv(glGetUniformLocation(programID, name.c_str()), static_cast<GLsizei>(count), values);
}