// main.cpp
// Written in WSL
// A simple OpenGL program that creates a window and clears it with a color.
// Uses GLFW for window/context management and GLAD for OpenGL function loading.
// On WSL, alias glcompile='cd /mnt/c/Users/your user/OneDrive/Desktop/everything/GLSL 
// g++ src/main.cpp src/glad.c -Iinclude -Iglfw-3.4/include glfw-3.4/build/src/libglfw3.a -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o app && ./app'
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Callback: adjust viewport on window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Process input each frame
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // GLFW window hints: OpenGL 3.3 core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // only needed on macOS

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "4.5 (Core Profile) Mesa 25.2.6-1", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // Make context current
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGL())
    {
        std::cerr << "Failed to initialize GLAD\n";
        glfwTerminate();
        return -1;
    }

    // Now it is safe to query GPU / GL info
    std::cout << "GPU Vendor:   " << glGetString(GL_VENDOR)   << '\n';
    std::cout << "GPU Renderer: " << glGetString(GL_RENDERER) << '\n';
    std::cout << "GL Version:   " << glGetString(GL_VERSION)  << '\n';

    // Set initial viewport and callback
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Rendering commands
        glClearColor(0.5f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glfwTerminate();
    return 0;
}
