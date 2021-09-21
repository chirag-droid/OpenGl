#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

// Window dimensions
const unsigned int WIDTH = 800, HEIGHT = 600;

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f, -0.5f, 0.0f,
     0.5f / 2, 0.0f, 0.0f,
    -0.5f / 2, 0.0f, 0.0f
};

unsigned int indices[] = {
    0, 3, 5,
    3, 2, 4,
    5, 4, 1
};

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

    Shader shader("res/shaders/basic.glsl");

    VertexArray vertexArray;
    vertexArray.Bind();

    VertexBuffer vertexBuffer(vertices, 6 * 3 * sizeof(float));
    IndexBuffer indexBuffer(indices, 9);

    VertexBufferLayout vertexLayout;
    vertexLayout.Push(GL_FLOAT, 3);
    vertexArray.AddBuffer(vertexBuffer, vertexLayout);

    vertexArray.Unbind();
    vertexBuffer.Unbind();
    indexBuffer.Unbind();

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear the colorbuffer
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Activate the shader program
        shader.Activate();
        vertexArray.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        // Listen for key press, mouse events etc. and swap the buffer
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    // Terminates GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}
