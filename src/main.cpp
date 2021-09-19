#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

struct ShaderProgramSources {
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSources ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

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

static GLuint CompileShader(GLenum type, const std::string& source) {
    GLuint id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    // TODO: Error handling

    return id;
}

static GLuint CreateShader(const std::string& vertexShader, std::string& fragmentShader) {
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

int main()
{
    std::cout << "Starting GLFW context." << std::endl;
    // Init GLFW
    glfwInit();

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    // Load glad so it configures OpenGl
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    // Get Opengl version 
    std::cout << "OpenGl version - " << glGetString(GL_VERSION) << std::endl;

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSwapInterval(1);

    ShaderProgramSources source = ParseShader("res/shaders/basic.glsl");
    GLuint shaderProgram = CreateShader(source.VertexSource, source.FragmentSource);

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    // Terminates GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}
