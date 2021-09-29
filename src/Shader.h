#pragma once

#include <string>
#include <unordered_map>

struct ShaderProgramSources {
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
    unsigned int m_ID;

    // Maps name of the uniform to its location(int)
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(const std::string& filePath);
    ~Shader();

    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniform3f(const std::string& name, float v0, float v1, float v2);

    void Bind();
    void Unbind();
private:
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int CompileShader(unsigned int type, const std::string& source);

    int GetUniformLocation(const std::string& name);
};

ShaderProgramSources ParseShader(const std::string& filePath);