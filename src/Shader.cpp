#include <string>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

#include "Shader.h"

ShaderProgramSources ParseShader(const std::string& filePath) {
    std::ifstream stream(filePath);

    enum ShaderType {
        NONE = -1, VERTEX, FRAGMENT
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    // If the file is not open {"", ""} is returned
    if (!stream.is_open()) return {"", ""};

    // Iterates over each line in the file
    while(stream.good()) {
        std::getline(stream, line);

        if (line.find("#shader vertex") != std::string::npos)
            type = ShaderType::VERTEX;
        else if (line.find("#shader fragment") != std::string::npos)
            type = ShaderType::FRAGMENT;
        else
            ss[(int)type] << line << "\n";
    }

    return { ss[0].str(), ss[1].str() };
}

Shader::Shader(const std::string& filePath) {
    ShaderProgramSources source = ParseShader(filePath);
    m_ID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() {
    glDeleteProgram(m_ID);   
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    GLuint program = glCreateProgram();
    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // Delete shaders because we have attached it with program
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    GLuint id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    // TODO: Error handling

    return id;
}

void Shader::Bind() {
    glUseProgram(m_ID);
}

void Shader::Unbind() {
    glUseProgram(0);
}