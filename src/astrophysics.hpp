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

namespace celestial
{
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


            double distance_to(std::array<double,2> target) const
            {
                return std::sqrt( 
                    (target[0] - pos[0]) * (target[0] - pos[0])  +  
                    (target[1] - pos[1]) * (target[1] - pos[1]) 
                ); // sqrt(a^2 + b^2)
            }


            double attraction_to(celestial_body& target) const
            {
                double d = distance_to(target.pos);
                return G * (target.mass + mass) / (d*d); // G * (m1+m2)/d^2;
            }


            double velocity()
            {
                return std::sqrt( (motion_vector[0]*motion_vector[0]) + (motion_vector[1]*motion_vector[1]) ); // v = sqrt(x^2 + y^2)
            }


            std::vector<std::array<double,2>> calculate_trajectory(int steps) const
            {
                std::array<double,2> projected_pos = pos;
                std::vector<std::array<double,2>> calculated_positions = {projected_pos};
                for (int i = 0; i < abs(steps); i++)
                {
                    projected_pos[0] += (2*(int)sign(steps)-1) * motion_vector[0];
                    projected_pos[1] += (2*(int)sign(steps)-1) * motion_vector[1];

                    calculated_positions.push_back(projected_pos);
                }
                return calculated_positions;
            }
    };



    class planet : public celestial_body
    {
        public:

            float c_colour[3];
            float brightness;

            planet(float mass_arg, const std::array<double, 2>& pos_arg, const std::array<double, 2>& motion_vector_arg, const float colour_arg[3], float brightness_arg = 1.0f): 
                celestial_body(mass_arg, pos_arg, motion_vector_arg), 
                brightness(brightness_arg)
            {
                for (int i = 0; i < 3; ++i) c_colour[i] = colour_arg[i];
            }



            void orbit(celestial_body& target, bool clockwise = true) // Force the planet into a perfectly circular orbit around the target
            {
                double tangential_gradient = -1 * (target.pos[0] - pos[0])/(target.pos[1] - pos[1]); // Potential division by zero error; TODO: Tangent vector

                double orbital_velocity = std::sqrt(G * (target.mass + mass) / distance_to(target.pos));  // sqrt( G * (m1+m2)/d ) // NOT d^2, I KNOW, IT *IS* SIMILAR TO THE DEFINITION OF ATTRACTION <3

                double horizontal_acceleration = orbital_velocity /  sqrt(1 + (tangential_gradient*tangential_gradient));
                double vertical_acceleration = tangential_gradient*horizontal_acceleration;

                if (!clockwise)
                {
                    horizontal_acceleration *= -1;
                    vertical_acceleration *= -1;
                }

                motion_vector[0] = target.motion_vector[0] + horizontal_acceleration;
                motion_vector[1] = target.motion_vector[1] + vertical_acceleration;
            }
    };



    class star : public celestial_body
    {
        public:

            float c_colour[3];
            float luminosity;

            star(float mass_arg, const std::array<double, 2>& pos_arg, const std::array<double, 2>& motion_vector_arg, const float colour_arg[3], float luminosity_arg): 
                celestial_body(mass_arg, pos_arg, motion_vector_arg),
                luminosity(luminosity_arg)
            {
                for (int i = 0; i < 3; ++i) c_colour[i] = colour_arg[i];
            }

            

            double intensity_at(std::array<double,2> target)
            {
                double distance = distance_to(target);
                return luminosity / (distance*distance); // L/d^2
            }
    };
}


#endif