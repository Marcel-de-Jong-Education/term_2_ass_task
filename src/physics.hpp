#ifndef ASTROPHYSICS
#define ASTROPHYSICS

#include <iostream> // for debugging

#include <cmath>

#include <array>
#include <vector>

const float G = 1.0f; // gravitational constant

bool sign(long long num)
{
    return (unsigned long long)num >> 63; // 0 -> positive; 1 -> negative
}

class celestial_body
{
    public:

        float mass;
        std::array<double, 2> pos;
        std::array<double, 2> motion_vector;
        float c_colour[3] = { 0.9f, 0.9f, 0.9f };

        celestial_body(float mass_arg, const std::array<double, 2>& pos_arg, const std::array<double, 2>& motion_vector_arg):
            mass(mass_arg),
            pos(pos_arg),
            motion_vector(motion_vector_arg)
        {}

        void update_position()
        {
            pos[0] += motion_vector[0];
            pos[1] += motion_vector[1];
        }

        std::vector<std::array<double,2>> calculate_trajectory(int steps)
        {
            std::array<double,2> projected_pos = pos;
            std::vector<std::array<double,2>> calculated_positions = {projected_pos};
            for (int i = 0; i < abs(steps); i++)
            {
                projected_pos[0] += (2*sign(steps)-1) * motion_vector[0];
                projected_pos[1] += (2*sign(steps)-1) * motion_vector[1];

                calculated_positions.push_back(projected_pos);
            }
            return calculated_positions;
        }
};



class planet : public celestial_body
{
    public:

        float c_colour[3];

        planet(float mass_arg, const std::array<double, 2>& pos_arg, const std::array<double, 2>& motion_vector_arg, const float colour_arg[3]): 
            celestial_body(mass_arg, pos_arg, motion_vector_arg)
        {
            for (int i = 0; i < 3; ++i) c_colour[i] = colour_arg[i];
        }



        void orbit(celestial_body target)
        {
            float distance = std::sqrt(target.pos[0] - pos[0]) * (target.pos[0] - pos[0])  +  (target.pos[1] - pos[1]) * (target.pos[1] - pos[1]); // sqrt(a^2 + b^2)

            float attraction = G * (target.mass + mass) / (distance * distance); // G * (m1+m2)/d^2

            float tangential_gradient = -1 * (target.pos[0] - pos[0])/(target.pos[1] - pos[1]); // 

            float net_force = std::sqrt((distance*distance) - distance + (attraction*attraction)); // total force exerted

            float horizontal_force = std::sqrt( (net_force*net_force) / (1 + (tangential_gradient*tangential_gradient)) );
            float vertical_force = tangential_gradient*horizontal_force;

            motion_vector[0] = target.motion_vector[0] + horizontal_force;
            motion_vector[1] = target.motion_vector[1] + vertical_force;
        }
};


#endif