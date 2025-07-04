#ifndef ASTROPHYSICS
#define ASTROPHYSICS

#include <iostream> // for debugging

#include <cmath> // I hope it is apparent why a module for mathematical functions would be valuable in such a mathematics-heavy project
#include <vector> // because c-arrays and linked-lists arent as good

const double G = 0.000000000066743; // gravitational constant
const double entropy = 1 + 0*0.99999999; // 1 = perfect, 0 = all energy lost instantly

bool sign(long long num) // is a number negative?
{
    return (unsigned long long)num >> 63; // 0 -> positive; 1 -> negative
}

namespace celestial // 
{
    class celestial_body // parent class of all objects
    {
        public: // dont need private parts anyway lolll

            double mass; // In kilogrammes
            double elasticity; //
            std::vector<double> pos; // coordinates of this thing
            std::vector<double> motion_vector; // motion in orthogonal directions of this thing
            float c_colour[3] = { 0.9f, 0.9f, 0.9f }; // a default off-white colour; might change it later idk
			double radius;
		

            celestial_body(float mass_arg, const std::vector<double>& pos_arg, const std::vector<double>& motion_vector_arg): // initialise 
                mass(mass_arg), // send mass
                pos(pos_arg), // send position
                motion_vector(motion_vector_arg) // send motion
            {
				radius = sqrt(mass)/128.0;
			}



            void update_position() // update the position according to the motion vector
            {
                // add motion to position
                pos[0] += motion_vector[0];
                pos[1] += motion_vector[1];

                // there was a really good reason ill remember later why it is 1x-0 and not just... x
                pos[0] = 1 * (pos[0] - std::floor(pos[0])) - 0; 
                pos[1] = 1 * (pos[1] - std::floor(pos[1])) - 0;
                
                // probably shouldnt be done seperately but this is nice, simple and easy. plus u cant even tell!
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


            double distance_to(std::vector<double> target) const // returns distance from object to a set of coordinates
            {
                return std::sqrt
                ( 
                    (target[0] - pos[0]) * (target[0] - pos[0])  +  
                    (target[1] - pos[1]) * (target[1] - pos[1]) 
                ); // sqrt(dx^2 + dy^2)
            }


            double speed() const
            {
                return std::sqrt( (motion_vector[0]*motion_vector[0]) + (motion_vector[1]*motion_vector[1]) ); // v = sqrt(x^2 + y^2)
            }



            double relative_speed(const celestial_body& target) const // returns difference of motion vectors
            {
				return sqrt(
					(motion_vector[0] - target.motion_vector[0])*(motion_vector[0] - target.motion_vector[0]) // dx_v^2
					+
					(motion_vector[1] - target.motion_vector[1])*(motion_vector[1] - target.motion_vector[1]) // dy_v^2
				);
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


            std::vector<std::vector<double>> calculate_trajectory(int steps) const // returns a list of positions the object is EXPECTED to be (or have been for negative input)
            {
                std::vector<double> projected_pos = pos; // start at object position
                std::vector<std::vector<double>> calculated_positions = {projected_pos}; // initialise vector to store projected positions
                for (int i = 0; i < abs(steps); i++) // for however far in the future we want to estimate
                {
                    // (2*(int)sign(steps)-1) is 1 if steps is positive and -1 if steps is negative; so this method can calculate BACKWARDS in time
                    projected_pos[0] += (2*(int)sign(steps)-1) * motion_vector[0]; 
                    projected_pos[1] += (2*(int)sign(steps)-1) * motion_vector[1];
                    //

                    calculated_positions.push_back(projected_pos); // add the position to the vector
                }
                return calculated_positions; //
            }



            std::vector<double> gravitational_force_to(const celestial_body& target) const // returns a vector containing the gravitational force to a target body in the form [0]horizonal [1]vertical [2]total
            {
                double distance = distance_to(target.pos); // get the distance to the target
                if (distance == 0) // we're meant to divide by distance later so~
                {
                    std::cout <<  "WARNING: DIVISION BY ZERO!\n\n"; // this is extremely rare so if it happens itd be cool to know about it!!
                    return std::vector<double>{0,0,0}; // just return 0 and avoid nonsense
                }
		    	// given mass is in kg and distance is in metres
			// G*m_1*m_2 / d^2 
                double force = G * (mass * target.mass) / (distance*distance); 
			// F = ma
			// a = F/m
                double self_force = force / mass; // account for inertia
		    
                double dx = target.pos[0]-pos[0]; // x1 - x2
                double dy = target.pos[1]-pos[1]; // y1 - y2

                double force_distance = std::sqrt((dx*dx) + (dy*dy)); // c = sqrt(a^2 + b^2)
                
                return // 
                {
                    dx/force_distance * self_force, // horizontal force
                    dy/force_distance * self_force, // vertical force
                    self_force // total force
                };
            }



            std::vector<double> calculate_gravitational_imbalance(std::vector<celestial_body>& objects) const // returns a vector of the net force of all objects on this object gravitationally split orthogonally
            {
                std::vector<double> imbalance = {0,0}; // {x, y}
                for (celestial_body& object : objects) // check all objects
                {
                    if (&object != this) // because distance to the self can uhm cause problems
                    {
                        // contribute object's pull on this object (look i know the nomenclature is being mildly confusing please just bare with it kay? <3)
                        imbalance[0] += gravitational_force_to(object)[0];
                        imbalance[1] += gravitational_force_to(object)[1];
                    }
                }
                return imbalance; //
            }




            bool detect_collision(celestial_body& target) const // returns if an object is inside another
            {
                return (distance_to(target.pos) < (radius + target.radius)/2); // 
            }



            void reflect(celestial_body& target) // https://cdn.tutsplus.com/gamedev/uploads/legacy/031_whenWorldsCollide/wikigif.gif
            {
                // find vector and the normal
                
                double distance = distance_to(target.pos); // 
                double dx = target.pos[0] - pos[0]; // x_2 - x_1
                double dy = target.pos[1] - pos[1]; // y_2 - y_1

                // distance/velocity == dx/x_vector == dy/y_vector
				double impact_speed = relative_speed(target);
                double scale_factor == distance/impact_speed);
                // therefore
                double x_vector_unit = dx*scale_factor; // how much x velocity for every 1 speed
                double y_vector_unit = dy*scale_factor; // how much y velocity for every 1 speed
            }



            void correct_overlap(celestial_body& target) // assumes objects are already overlapping
            {
                double distance = distance_to(target.pos);
                double overlapping_distance = (radius + target.radius)/2 - distance; // r_1 + r_2 - d

                double dx = target.pos[0] - pos[0]; // x_2 - x_1
                double dy = target.pos[1] - pos[1]; // y_2 - y_1

                double horizontal_overlap = dx / distance * overlapping_distance; // for every unit of distance we get this much horizontal overlap, then multiply by the overlapping distance as the scale factor
                double vertical_overlap = dy / distance * overlapping_distance; // ditto above

                // heavier objects move less and lighter objects move more
                double mass_ratio = mass / (mass + target.mass);
                double target_mass_ratio = target.mass / (mass + target.mass);

                // move object 
                pos[0] -= horizontal_overlap * target_mass_ratio;
                pos[1] -= vertical_overlap * target_mass_ratio;
                // move target
                target.pos[0] += horizontal_overlap * mass_ratio;
                target.pos[1] += vertical_overlap * mass_ratio;

                reflect(target);
            }
    };



    class planet : public celestial_body // planet is a child to the parent class celestial_body
    {
        public:

            float c_colour[3]; // an array of RGB of FLOATS because we do things differnetly here in openGL land
            float brightness; // intended to reflect how much light is being received from stars (pun intended!!)

            planet(float mass_arg, const std::vector<double> pos_arg, const std::vector<double> motion_vector_arg,  std::vector<float> colour_arg): // initialise in a slightly different and annoying way from regular celestial_bodys (not typing *celestial_bodies* hurt me more than it hurt you, trust me)
                celestial_body(mass_arg, pos_arg, motion_vector_arg)
            {
                for (int i = 0; i < 3; ++i) c_colour[i] = colour_arg[i]; // a vector can ONLY be initialised like this in this context for some reason
            }



            void orbit(celestial_body& target, bool clockwise = true) // Force the planet into a perfectly circular orbit around the target
            {
                double tangential_gradient = -1 * (target.pos[0] - pos[0])/(target.pos[1] - pos[1]); // Potential division by zero error; TODO: Tangent vector

                double orbital_velocity = std::sqrt(G * (target.mass + mass) / distance_to(target.pos));  // sqrt( G * (m1+m2)/d ) // NOT d^2, I KNOW, IT *IS* SIMILAR TO THE DEFINITION OF ATTRACTION <3

                double horizontal_acceleration = orbital_velocity /  sqrt(1 + (tangential_gradient*tangential_gradient)); 
                double vertical_acceleration = tangential_gradient*horizontal_acceleration;

                if (!clockwise) // if its counterclockwise just multiply acceleration by -1
                {
                    horizontal_acceleration *= -1;
                    vertical_acceleration *= -1;
                }
                //
                // we add the target's motion as well as the acceleration to make the orbit relative to them as a stationary object
                motion_vector[0] = target.motion_vector[0] + horizontal_acceleration;
                motion_vector[1] = target.motion_vector[1] + vertical_acceleration;
                //
            }
    };



    class star : public celestial_body // oh my STARS! a child class of the parent class celestial_body
    {
        public:

            float c_colour[3]; // ditto planet colours
            float luminosity; // i want my stars to *shine* one day!!

            star(float mass_arg, const std::vector<double>& pos_arg, const std::vector<double>& motion_vector_arg, const float colour_arg[3], float luminosity_arg): // initialise~~
                celestial_body(mass_arg, pos_arg, motion_vector_arg), // as a celestial body first
                luminosity(luminosity_arg) // glowy!
            {
                for (int i = 0; i < 3; ++i) c_colour[i] = colour_arg[i]; // ditto planet vector initialisation
            }

            

            double intensity_at(std::vector<double> target) // returns how bright light from star is at a given position
            {
                double distance = distance_to(target);
                return luminosity / (distance*distance); // L/d^2
            }
    };
}


#endif
