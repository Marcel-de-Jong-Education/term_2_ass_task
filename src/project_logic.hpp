#ifndef PROJECT_LOGIC
#define PROJECT_LOGIC
#include "astrophysics.hpp"

namespace project_logic
{
    void sim_loop(std::vector<celestial::celestial_body>& objects)
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
            object.update_position();
        }
    }
}

#endif