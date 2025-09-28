#pragma once
#include <string>
#include <glad/glad.h>

class Shader
{
private:
    unsigned int programID;

    static void CheckCompileErrors(unsigned int shader, const std::string &type);

public:
    Shader();
    ~Shader();

    bool LoadFromFiles(const std::string &vertexPath, const std::string &fragmentPath);
    bool LoadFromSource(const std::string &vertexSource, const std::string &fragmentSource);

    void Use() const;

    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;
    void SetVec2(const std::string &name, float x, float y) const;
    void SetVec3(const std::string &name, float x, float y, float z) const;
    void SetVec4(const std::string &name, float x, float y, float z, float w) const;
    void SetIntArray(const std::string &name, const int *values, uint32_t count) const;

    [[nodiscard]] unsigned int GetProgramID() const { return programID; }
};