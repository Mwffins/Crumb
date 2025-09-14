#pragma once
#include <string>
#include <glad/glad.h>

class Shader
{
private:
    unsigned int programID;

    void CheckCompileErrors(unsigned int shader, const std::string &type);

public:
    Shader();
    ~Shader();

    bool LoadFromFiles(const std::string &vertexPath, const std::string &fragmentPath);
    bool LoadFromSource(const std::string &vertexSource, const std::string &fragmentSource);

    void Use();

    void SetBool(const std::string &name, bool value);
    void SetInt(const std::string &name, int value);
    void SetFloat(const std::string &name, float value);
    void SetVec2(const std::string &name, float x, float y);
    void SetVec3(const std::string &name, float x, float y, float z);
    void SetVec4(const std::string &name, float x, float y, float z, float w);
    void SetIntArray(const std::string &name, int *values, uint32_t count);

    unsigned int GetProgramID() const { return programID; }
};