#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

#include "Shader.h"

Shader::Shader(const std::string& filePath) {
    ShaderProgramSources source = ParseShader(filePath);
    m_ID = CreateShader(source.VertexSource, source.FragmentSource);
}

// Shader destructor
Shader::~Shader() {
    glDeleteProgram(m_ID);   
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2) {
    glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

// Private function to get location of a uniform
int Shader::GetUniformLocation(const std::string& name) {
    // If name exist in location cache return location
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    // If location doesn't exist in cache, get the location
    int location = glGetUniformLocation(m_ID, name.c_str());
    if (location == -1)
        std::cout << "Warning: Uniform " << name << " doesn't exists." << std::endl;

    // Now, push the location int the cache
    m_UniformLocationCache[name] = location;
    return location;
}

void Shader::Bind() {
    glUseProgram(m_ID);
}

void Shader::Unbind() {
    glUseProgram(0);
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    GLuint program = glCreateProgram();
    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    // Attach the vertex and fragment shaders to the program
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    // Link and validate the program
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

// ParseShader takes a path in argument and parses it and returns ShaderProgramSources
ShaderProgramSources ParseShader(const std::string& filePath) {
    // Open the file stream
    std::ifstream stream(filePath);

    // Define the ShaderType enum
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

        // If #shader vertex is found, set type to vertex
        // which pushes the upcoming lines to 0 index of ss
        if (line.find("#shader vertex") != std::string::npos)
            type = ShaderType::VERTEX;

        // If #shader fragment is found, set type to fragment
        else if (line.find("#shader fragment") != std::string::npos)
            type = ShaderType::FRAGMENT;

        // If the line is a normal line, just push it in ss with index type
        else
            ss[(int)type] << line << "\n";
    }

    return { ss[0].str(), ss[1].str() };
}
