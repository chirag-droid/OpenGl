#pragma once

#include <string>

struct ShaderProgramSources {
    std::string VertexSource;
    std::string FragmentSource;
};

ShaderProgramSources ParseShader(const std::string& filePath);

class Shader
{
private:
    unsigned int m_ID;
public:
    Shader(const std::string& filePath);
    ~Shader();

    void Bind();
    void Unbind();
private:
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int CompileShader(unsigned int type, const std::string& source);
};