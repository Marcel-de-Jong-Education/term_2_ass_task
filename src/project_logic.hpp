#ifndef PROJECT_LOGIC
#define PROJECT_LOGIC
#include "astrophysics.hpp"
#include <renderer.hpp>

#include <windows.h>
#include <shellapi.h>

#include <functional> // so we can pass functions as arguments!

#include <string> // managing text in console is easier

namespace project_logic
{
    extern std::vector<celestial::celestial_body>* bodies;


    inline void sim_loop(std::vector<celestial::celestial_body>& objects)
    {
        // Calculate new motions based on gravity
        std::vector<double> gravitational_moment = {0,0};
        for (celestial::celestial_body& object : objects) // find forces
        {
            gravitational_moment = object.calculate_gravitational_moment(objects);

            object.motion_vector[0] += gravitational_moment[0];
            object.motion_vector[1] += gravitational_moment[1];
        }

        // Collision handling TODO


        for (celestial::celestial_body& object : objects) // update positions
        {
            object.limit_orthogonal_velocity(0.1);
            object.update_position();
        }
    }





    inline void get_bodies(std::vector<celestial::celestial_body>& extern_bodies)
    {
        bodies = &extern_bodies;
    }




    inline void skip_if_blank_input(std::string input) // todo, maybe
    {

    }




    inline void user_create_object(int xpos, int ypos)
    {
        std::vector<int> window_dimensions = render::export_window_dimensions();

        float mass;
        std::vector<double> position = {};
        std::vector<double> motion = {};

        std::cout << "Enter object mass:\n";
        while (true)
        {
            std::cin >> mass;
            if (std::cin.fail()) 
            {
                std::cerr << "Invalid input. Stop trying to break my code! (also you have to try again now nyahahaha!)\n"; std::cin.clear(); std::cin.ignore(10000, '\n'); // Error handling
            } 
            else 
            {
                break;
            }
        }




        std::string line;
        std::cout << "Enter object x position:\n";

        
        std::getline(std::cin, line);
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
                    break;
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
                    break;
                }
            }
        } 
        else // no input, so default to clicked position
        {
            position.push_back((double)ypos / (double)window_dimensions[1]);
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
                    break;
                }
            }
        } 
        else // no input, so default to zero!
        {
            motion.push_back(0.0); 
        }




        // oms, whomever might be reading this, u just made it thru the most disgusting part of my code (i hope)!! u should have a gold star

        bodies->push_back(celestial::celestial_body(mass, position, motion));
    }





    inline void open_terminal_at(int x, int y) // 
    {
        FreeConsole(); // detach from whatever console used to exist

        AllocConsole(); // new console!! yay!

        HWND consoleWnd = GetConsoleWindow();
        if (consoleWnd) MoveWindow(consoleWnd, x, y, 800, 500, TRUE);

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




    inline void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) // If LMB click
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            std::cout << "Mouse click at: (" << xpos << ", " << ypos << ")\n";

            open_terminal_at((int)xpos,(int)ypos);
        }
    }    
}

#endif