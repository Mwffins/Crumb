#include "Shader.h"

Shader::Shader() : programID(0) {
}

Shader::~Shader() {
    if (programID != 0) {
        glDeleteProgram(programID);
    }
}

bool Shader::LoadFromFiles(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexCode = ReadFile(vertexPath);
    std::string fragmentCode = ReadFile(fragmentPath);
    
    if (vertexCode.empty() || fragmentCode.empty()) {
        std::cout << "ERROR: Failed to read shader files" << std::endl;
        return false;
    }
    
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");
    
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
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

void Shader::Use() {
    glUseProgram(programID);
}

std::string Shader::ReadFile(const std::string& filepath) {
    std::ifstream file;
    std::stringstream stream;
    
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try {
        file.open(filepath);
        stream << file.rdbuf();
        file.close();
        return stream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR: Failed to read file: " << filepath << std::endl;
        return "";
    }
}

void Shader::CheckCompileErrors(unsigned int shader, const std::string& type) {
    int success;
    char infoLog[1024];
    
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR: Shader compilation failed (" << type << "): " << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR: Program linking failed: " << infoLog << std::endl;
        }
    }
}

void Shader::SetBool(const std::string& name, bool value) {
    glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::SetVec2(const std::string& name, float x, float y) {
    glUniform2f(glGetUniformLocation(programID, name.c_str()), x, y);
}

void Shader::SetVec3(const std::string& name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(programID, name.c_str()), x, y, z);
}

void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(programID, name.c_str()), x, y, z, w);
}