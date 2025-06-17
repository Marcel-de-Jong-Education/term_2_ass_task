// https://learnopengl.com/Getting-started/Hello-Window
// these 3 includes are just for graphics
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "shader_s.hpp"
//
// these are both headers I fully wrote myself for this project!!
#include "astrophysics.hpp"
#include "project_logic.hpp"
//

std::vector<celestial::celestial_body> celestial_bodies = {}; // a vector of all the objects that fly around!
std::vector<celestial::celestial_body>* project_logic::bodies = nullptr; // so the project_logic header can monipulate the celestial_bodies vector

unsigned int initial_object_count = 32; // how many objects are there at the start of the programme


 
void processInput(GLFWwindow *window)  // simple function to manage input to the window
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() // this is so C++ 101 im not going to explain (even tho it would have been easier than typing this XP)
{
    std::cout << "Hello, World!" << std::endl; // first sign of life when the programme starts

    GLFWwindow* window = renderer::init(2048, 1024, 1); // INITIALISE THE RENDERER 🔥🔥🔥
    
    //// SHADERS ////
    Shader ourShader("./shader.vert", "./shader.frag"); // the programme breaks if these arent in the same place as the executable


    renderer::colour default_body_colour; // initialise the default colour of the bodies! maybe the code IS the comment sometimes...
    default_body_colour.rgb = {0.9f, 0.9f, 0.9f}; // i decided that planets need a colour argument unlike the celestial_body parent for some reason so this needs to be here 


    for (unsigned int i = 0; i < initial_object_count; i++) // spawn initial_object_count amount of objects
    {
        celestial_bodies.push_back // append to the celestial_bodies vector
        (
            celestial::planet // MAKING A PLANET IM A DEITY WOWWWOWOWOWOW
            (
                (float(i+1) / initial_object_count), // mass ranges from very small to 1 :)
                std::vector<double>{0.1*i - 0.9, 0.2*i - 0.4},  // spawn positions are spread so they dont divide by zero, that would be bad (or not, since the error is actually handled!!)
                std::vector<double>{0,0}, // initial motion
                default_body_colour.rgb // colour
            )
        );
    }

    
    renderer::standard::circle default_circle; // default appearance for objects before we ✨customise✨ them
    default_circle.origin[0] = 0.0f; // xpos
    default_circle.origin[1] = 0.0f; // ypos
    default_circle.radius = 0.008f; // Percentage of window size

    

    std::vector<renderer::standard::circle> circle_list(celestial_bodies.size(), default_circle); // list of circles to draw; the *representatations* of the actual objects

    for (int i = 0; i < circle_list.size(); i++) // give ALL the objects a face! :D
    {
        // set the positions of the representations to that of the objects
        circle_list[i].origin[0] = (float)celestial_bodies[i].pos[0]; 
        circle_list[i].origin[1] = (float)celestial_bodies[i].pos[1]; 
        //

        circle_list[i].radius = celestial_bodies[i].radius; // the size of the objects is preportional to the sqrt of their mass!; 64^-1 just feels right idk
    }


    project_logic::get_bodies(celestial_bodies); // so the project logic actually can access the vector of objects lol

    glfwSetMouseButtonCallback(window, project_logic::mouse_button_callback); // Instruct glfw to use the function defined in project_logic for mouseclicks

    while (!glfwWindowShouldClose(window)) // while the window isnt instructed to close
    {
        processInput(window); // if there has been input, *deal with it　😎* [insert explosion sfx meme here idk]

        glClearColor(0.15f, 0.10f, 0.20f, 1.0f); // background colour
        glClear(GL_COLOR_BUFFER_BIT);
        


        for (int i = 0; i < circle_list.size(); i++) // make a circle to render from the list of circle representation information objects 
        {
            // i had some bugs and making the positions 2x-1 fixed them, im not sure why but im not touching it!
            circle_list[i].origin[0] = (2 * (float)celestial_bodies[i].pos[0]) - 1; 
            circle_list[i].origin[1] = (2 * (float)celestial_bodies[i].pos[1]) - 1;
            render::standard::circle(circle_list[i], default_body_colour);
        }
        
        ourShader.use(); // DRAW !!!!!!!!

        glfwSwapBuffers(window); // put on the window
        glfwPollEvents(); // processes events in the event queue

        project_logic::sim_loop(celestial_bodies); // do all the physics calculations and things; basically, an actual simulation step happens here!

        // very digusting
        if (celestial_bodies.size() > circle_list.size()) // handles one new addition to the list of bodies at a time
        {
            circle_list.push_back(default_circle); // add a new template
            // set appropriate coordinates
            circle_list.back().origin[0] = (float)celestial_bodies.back().pos[0]; 
            circle_list.back().origin[1] = (float)celestial_bodies.back().pos[1]; 
            //
            circle_list.back().radius = celestial_bodies.back().radius; // size is calculated the same way as the other objects
        }
    }   

    // clean up at the end of the programme
    glfwTerminate(); 
    return 0; // Done!! 
}
