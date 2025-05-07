// https://learnopengl.com/Getting-started/Hello-Window

#include <cmath>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <renderer.hpp>
#include "shader_s.hpp"

#include "astrophysics.hpp"
#include "project_logic.hpp"


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

    renderer::get_window(window); // so renderer knows what the window is



    //// SHADERS ////
    Shader ourShader("./shader.vert", "./shader.frag");



    renderer::colour backgroundColour;
    backgroundColour.rgb[0] = 0.0f; // Black 
    backgroundColour.rgb[1] = 0.0f; // Black
    backgroundColour.rgb[2] = 0.0f; // Black

    renderer::colour default_body_colour;
    default_body_colour.rgb = {0.9f, 0.9f, 0.9f};


    for (int i = 0; i < 100; i++)
    {
        celestial_bodies.push_back(celestial::planet
            (
                float(i)/50, // mass
                std::vector<double>{0.1*i - 0.9,0.2*i - 0.4},  // position
                std::vector<double>{0.000002*i*i,-0.000003*i*i}, // motion
                default_body_colour.rgb // colour
            ));
    }

    
    renderer::circle default_circle;
    default_circle.origin[0] = 0.0f; // xpos
    default_circle.origin[1] = 0.0f; // ypos
    default_circle.radius = 0.008f; // Percentage of window size

    

    std::vector<renderer::circle> circle_list(celestial_bodies.size(), default_circle); // circles to draw, representatations of the actual objects

    for (int i = 0; i < circle_list.size(); i++)
    {
        circle_list[i].origin[0] = (float)celestial_bodies[i].pos[0]; 
        circle_list[i].origin[1] = (float)celestial_bodies[i].pos[1]; 

        circle_list[i].radius = sqrt(celestial_bodies[i].mass)/60;
    }





    renderer::init();

    while (!glfwWindowShouldClose(window)) 
    {
        processInput(window);

        glClearColor(0.15f, 0.10f, 0.20f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        


        for (int i = 0; i < circle_list.size(); i++)
        {
            circle_list[i].origin[0] = (2 * (float)celestial_bodies[i].pos[0]) - 1;
            circle_list[i].origin[1] = (2 * (float)celestial_bodies[i].pos[1]) - 1;
            render::circle(circle_list[i], default_body_colour);
        }
        
        ourShader.use();

        glfwSwapBuffers(window);
        glfwPollEvents();

        project_logic::sim_loop(celestial_bodies);
        //std::cout << celestial_bodies[0].pos[0] << ", " << celestial_bodies[0].pos[1] << '\n';
    }   

    glfwTerminate();
    return 0;
}