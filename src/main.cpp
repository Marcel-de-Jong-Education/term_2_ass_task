// https://learnopengl.com/Getting-started/Hello-Window

#include <cmath>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <renderer.hpp>
#include "shader_s.hpp"

#include "astrophysics.hpp"


std::vector<celestial::celestial_body> celestial_bodies = {};


void framebuffer_size_callback(GLFWwindow *window, int width, int height) 
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) 
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() 
{
    std::cout << "Hello, World!" << std::endl;

    // initialise GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    // initialise GLFW window
    GLFWwindow *window = glfwCreateWindow(2048, 1024, "glThings", NULL, NULL);
    if (window == NULL) 
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // initialise GLAD function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }



    //// SHADERS ////
    Shader ourShader("./shader.vert", "./shader.frag");



    renderer::colour backgroundColour;
    backgroundColour.rgb[0] = 0.0f; // Black 
    backgroundColour.rgb[1] = 0.0f; // Black
    backgroundColour.rgb[2] = 0.0f; // Black

    renderer::circle tmpCircle;
    tmpCircle.origin[0] = 0.0f; // xpos
    tmpCircle.origin[1] = 0.0f; // ypos
    tmpCircle.radius = 0.95f; // Percentage of window size







    renderer::init();

    while (!glfwWindowShouldClose(window)) 
    {
        processInput(window);

        glClearColor(
          /*
          (sin(glfwGetTime() + (3.14f / 3 * 3)) + 1.0f) / 2.0f, // red
          (sin(glfwGetTime() + (3.14f / 3 * 2)) + 1.0f) / 2.0f, // green
          (sin(glfwGetTime() + (3.14f / 3 * 1)) + 1.0f) / 2.0f, // blue
          */
          0.15f, 0.10f, 0.20f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        render::circle(tmpCircle, backgroundColour);

        
        
        ourShader.use();

        glfwSwapBuffers(window);
        glfwPollEvents();

    }


    /*
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    */
    glfwTerminate();
    return 0;
}