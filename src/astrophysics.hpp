#ifndef ASTROPHYSICS
#define ASTROPHYSICS

#include <iostream> // for debugging

#include <cmath>

#include <array>
#include <vector>

const double G = -0.00000001; // gravitational constant
const double entropy = 0.995; // 1 = perfect, 0 = all energy lost instantly

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
            std::vector<double> pos;
            std::vector<double> motion_vector;
            float c_colour[3] = { 0.9f, 0.9f, 0.9f };

            celestial_body(float mass_arg, const std::vector<double>& pos_arg, const std::vector<double>& motion_vector_arg):
                mass(mass_arg),
                pos(pos_arg),
                motion_vector(motion_vector_arg)
            {}



            void update_position()
            {
                pos[0] += motion_vector[0];
                pos[1] += motion_vector[1];

                pos[0] = 1 * (pos[0] - std::floor(pos[0])) - 0; 
                pos[1] = 1 * (pos[1] - std::floor(pos[1])) - 0;
                

                motion_vector[0] *= entropy;
                motion_vector[1] *= entropy;
            }


            void debug_position() // manually set object position
            {
                std::cout << "\nEnter x: ";
                std::cin >> pos[0];
                std::cout << "\nEnter y: ";
                std::cin >> pos[1];
                std::cout << "\n\n";
            }


            double distance_to(std::vector<double> target) const
            {
                return std::sqrt( 
                    (target[0] - pos[0]) * (target[0] - pos[0])  +  
                    (target[1] - pos[1]) * (target[1] - pos[1]) 
                ); // sqrt(a^2 + b^2)
            }


            double velocity() const
            {
                return std::sqrt( (motion_vector[0]*motion_vector[0]) + (motion_vector[1]*motion_vector[1]) ); // v = sqrt(x^2 + y^2)
            }



            void limit_orthogonal_velocity(const double c) // if a body is going faster than c horizontally or vertically, it's speed is set to c
            {
                if (abs(motion_vector[0]) > c) 
                {
                    motion_vector[0] = (motion_vector[0] < 0) ? -c : c;
                }
                if (abs(motion_vector[1]) > c)
                {
                    motion_vector[1] = (motion_vector[1] < 0) ? -c : c;
                }
            }


            std::vector<std::vector<double>> calculate_trajectory(int steps) const
            {
                std::vector<double> projected_pos = pos;
                std::vector<std::vector<double>> calculated_positions = {projected_pos};
                for (int i = 0; i < abs(steps); i++)
                {
                    projected_pos[0] += (2*(int)sign(steps)-1) * motion_vector[0];
                    projected_pos[1] += (2*(int)sign(steps)-1) * motion_vector[1];

                    calculated_positions.push_back(projected_pos);
                }
                return calculated_positions;
            }



            std::vector<double> gravitational_force_to(const celestial_body& target) const
            {
                double distance = distance_to(target.pos);
                if (distance == 0) {std::cout <<  "WARNING: DIVISION BY ZERO!\n\n";}
                double net_force = G * (mass + target.mass) / (distance*distance); // G(m1+m2)/(d^2)
                double self_force = net_force * target.mass/(mass+target.mass);
                double dx = pos[0]-target.pos[0]; // x1 - x2
                double dy = pos[1]-target.pos[1]; // y2 - y2

                double force_distance = std::sqrt((dx*dx) + (dy*dy)); // c = sqrt(a^2 + b^2)
                
                return 
                {
                    dx/force_distance * self_force, // horizontal force
                    dy/force_distance * self_force, // vertical force
                    self_force // total force
                };
            }



            std::vector<double> calculate_gravitational_moment(std::vector<celestial_body>& objects) const
            {
                std::vector<double> moment = {0,0};
                for (celestial_body& object : objects) // because distance to the self can uhm cause problems
                {
                    if (&object != this)
                    {
                        moment[0] += gravitational_force_to(object)[0];
                        moment[1] += gravitational_force_to(object)[1];
                    }
                }
                return moment;
            }
    };



    class planet : public celestial_body
    {
        public:

            float c_colour[3];
            float brightness;

            planet(float mass_arg, const std::vector<double> pos_arg, const std::vector<double> motion_vector_arg,  std::vector<float> colour_arg): 
                celestial_body(mass_arg, pos_arg, motion_vector_arg)
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

            star(float mass_arg, const std::vector<double>& pos_arg, const std::vector<double>& motion_vector_arg, const float colour_arg[3], float luminosity_arg): 
                celestial_body(mass_arg, pos_arg, motion_vector_arg),
                luminosity(luminosity_arg)
            {
                for (int i = 0; i < 3; ++i) c_colour[i] = colour_arg[i];
            }

            

            double intensity_at(std::vector<double> target)
            {
                double distance = distance_to(target);
                return luminosity / (distance*distance); // L/d^2
            }
    };
}


#endif