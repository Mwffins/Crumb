#pragma once
#include <string>
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
private:
    unsigned int programID;

    std::string ReadFile(const std::string &filepath);

    void CheckCompileErrors(unsigned int shader, const std::string &type);

public:
    Shader();
    ~Shader();

    bool LoadFromFiles(const std::string &vertexPath, const std::string &fragmentPath);

    void Use();

    void SetBool(const std::string &name, bool value);
    void SetInt(const std::string &name, int value);
    void SetFloat(const std::string &name, float value);
    void SetVec2(const std::string &name, float x, float y);
    void SetVec3(const std::string &name, float x, float y, float z);
    void SetVec4(const std::string &name, float x, float y, float z, float w);

    unsigned int GetProgramID() const { return programID; }
};