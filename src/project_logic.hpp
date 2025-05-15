#ifndef PROJECT_LOGIC
#define PROJECT_LOGIC

#include <windows.h> // im assuming the marker runs windows 11 so im writing this for windows 11
#include <shellapi.h> // for the CLI stuff
#include "astrophysics.hpp" // definitions for the objects and their methods
#include <functional> // so we can pass functions as arguments!
#include <string> // managing text in CLI is easier
#include <renderer.hpp> // a graphics module

namespace project_logic
{
    extern std::vector<celestial::celestial_body>* bodies; // the vector of bodies in main.cpp shall be accessed locally via this!


    inline void sim_loop(std::vector<celestial::celestial_body>& objects) // one tick of the simulation
    {
        // Calculate new motion vectors based on gravity
        std::vector<double> gravitational_moment = {0,0}; // initialised outside the loop to save resources
        for (celestial::celestial_body& object : objects) // find forces
        {
            gravitational_moment = object.calculate_gravitational_moment(objects); // 

            // ADD and not SET the gravitational moment to conserve momentum!!
            object.motion_vector[0] += gravitational_moment[0]; 
            object.motion_vector[1] += gravitational_moment[1]; 
            //
        }

        // Collision handling TODO

        for (celestial::celestial_body& object : objects) // update positions
        {
            object.limit_orthogonal_velocity(0.1); // broken
            object.update_position(); //
        }
    }





    inline void get_bodies(std::vector<celestial::celestial_body>& extern_bodies) // retrieves the vector of celestial bodies for local use
    {
        bodies = &extern_bodies;
    }




    inline void skip_if_blank_input(std::string input) // todo, maybe
    {

    }




    inline void user_create_object(int xpos, int ypos) // allows the user to create an object!
    {
        std::vector<int> window_dimensions = render::export_window_dimensions(); // get the window dimensions

        float mass; // mass of the new object
        std::vector<double> position = {}; // position of the new object
        std::vector<double> motion = {}; // motion of the new object

        // take inputs //
        std::cout << "Enter object mass:\n";
        while (true) // keep trying until a good input retrieved
        {
            std::cin >> mass;
            if (std::cin.fail()) 
            {
                std::cerr << "Invalid input. Stop trying to break my code! (also you have to try again now nyahahaha!)\n"; std::cin.clear(); std::cin.ignore(10000, '\n'); // Error handling
            } 
            else 
            {
                break; // we have good input :)
            }
        }

        std::string line; // for retrieving input to be processed before use
        std::cout << "Enter object x position:\n";
        
        std::getline(std::cin, line);
        if (!line.empty()) // if there is an input
        {
            while (true) // keep trying until good input
            {
                std::stringstream ss(line); // get the line from CLI
                float pos_choice; // initialise pos_choice

                if (!(ss >> pos_choice)) // handle bad input
                {
                    std::cerr << "Invalid input. I'm tired of writing these error messages, so try again kindly.\n";
                } 
                else // handle *good* input
                {
                    position.push_back(pos_choice); //
                    std::cout << "x pos entered: " << pos_choice << '\n';
                    break; // stop trying! we have what we want!!
                }
            }
        } 
        else // no input, so default to clicked position
        {
            position.push_back((double)xpos / (double)window_dimensions[0]); // because for SOME REASON (definitely not me!!) position is PERCENTAGE ACROSS THE WINDOW, LOL
        }

        std::cout << "Enter object y position:\n";

        std::getline(std::cin, line); // yes i know im repeating the code here and maybe i could have just done a for-loop but tbh it felt too hard at the time of writing this to figure out
        if (!line.empty()) // if there is an input
        {
            while (true)
            {
                std::stringstream ss(line);
                float pos_choice;

                if (!(ss >> pos_choice)) 
                {
                    std::cerr << "Invalid input. I'm tired of writing these error messages, so try again kindly.\n";
                } 
                else 
                {
                    position.push_back(pos_choice);
                    std::cout << "y pos entered: " << pos_choice << '\n';
                    break;
                }
            }
        } 
        else // no input, so default to clicked position
        {
            position.push_back(1 - ((double)ypos / (double)window_dimensions[1])); // why is it 1 - x? i have no idea but it fixed the problem
        }


        // time to do THE EXACT SAME THING BUT FOR MOTION YAYYYY (ewie)


        std::cout << "Enter object x motion:\n";
        
        std::getline(std::cin, line); // oms a third time how dirty of me
        if (!line.empty()) // if there is an input
        {
            while (true)
            {
                std::stringstream ss(line);
                float mot_choice;

                if (!(ss >> mot_choice)) 
                {
                    std::cerr << "Invalid input. I'm tired of writing these error messages, so try again kindly.\n";
                } 
                else 
                {
                    motion.push_back(mot_choice);
                    std::cout << "x motion entered: " << mot_choice << '\n';
                    break;
                }
            }
        } 
        else // no input, so default to zero~~
        {
            motion.push_back(0.0); 
        }

        std::cout << "Enter object y motion:\n";

        std::getline(std::cin, line); // fourth time wow
        if (!line.empty()) // if there is an input
        {
            while (true)
            {
                std::stringstream ss(line);
                float mot_choice;

                if (!(ss >> mot_choice)) 
                {
                    std::cerr << "Invalid input. I'm tired of writing these error messages, so try again kindly.\n";
                } 
                else 
                {
                    motion.push_back(mot_choice);
                    std::cout << "y motion entered: " << mot_choice << '\n';
                    break;
                }
            }
        } 
        else // no input, so default to zero!
        {
            motion.push_back(0.0); 
        }




        // oms, whomever might be reading this, u just made it thru the most disgusting part of my code (i hope)!! u should have a gold star

        bodies->push_back(celestial::celestial_body(mass, position, motion)); // add the new object to the list in the main code
    }





    inline void open_terminal_at(int x, int y) // 
    {
        FreeConsole(); // detach from whatever console used to exist

        AllocConsole(); // new console!! yay!

        HWND consoleWnd = GetConsoleWindow(); // get console
        if (consoleWnd) MoveWindow // definite the CLI
        (
            consoleWnd, 
            x, y, // spawn position
            500, 800, // dimensions
            TRUE
        );

        // Redirect the I/O to the new console!!!
        FILE* fp;
        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONOUT$", "w", stderr);
        freopen_s(&fp, "CONIN$", "r", stdin);

        std::ios::sync_with_stdio();
        std::cout.clear();
        std::cin.clear();
        std::cerr.clear();

        user_create_object(x,y); // create object

        FreeConsole(); // done! :D
    }




    inline void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) // function for what to do if there is a mouse click
    {
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) // If LMB click
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos); // get cursor position
            //std::cout << "Mouse click at: (" << xpos << ", " << ypos << ")\n";

            open_terminal_at((int)xpos,(int)ypos); // open the CLI for the user to use!
        }
    }    
}

#endif
