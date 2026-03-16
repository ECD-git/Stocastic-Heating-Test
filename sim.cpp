#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>

// Real world consts
const float M = 1.00784*1.66*pow(10,-27); //[kg] //using atomic mass of H
const float k_B = 1.380649*pow(10, -23); //boltzmann const

// variable spaces
std::vector<float> LinSpace(float min, float max, int N)
{
    /*
    Generates a vector of evenly space points between min and max of length N
    Uses a lambda function to generate
    */
    // I made this with no prior knowledge of lambda functions haha we're so back
    std::vector<float> result(N);
    std::generate(result.begin(), result.end(), [n=0, &min, &max, &N] () mutable {++n; return min + (n-1)*((max-min)/(N-1));});
    return result;
}

// Random Functions
float RandomFloat(float min, float max)
{
    // generates a random float between a range min and max
    return min + static_cast <float> (std::rand()) / (static_cast <float> (RAND_MAX/(max-min)));
}
// Potential Functions
float PotentialSinSqr(float x, float t, float A, float k, float omega, float phi)
{
    /*
    Simple U = A sin^2{kx + omega t + phi} potential
    takes in all variables and returns a float of the potential in joules
    x expected in metres, time in s, omega in rad/s, A in joules, k in rad/m, phi in rad
    */
   return A*std::pow(std::sin((k*x) + (omega * t) + phi),2);
}
float ForceSinSqr(float x, float t, float A, float k, float omega, float phi)
{
    /*
    F = - dU/dx, so F = -kA sin(2[kx * omega t + phi])
    takes in all variables and returns a float of the potential in joules
    x expected in metres, time in s, omega in rad/s, A in joules, k in rad/m, phi in rad
    */
   return k*A*std::sin(2*((k*x)+(omega*t)+phi));
}

// main
int main()
{
    std::srand(time(0)); // seed uniform random num generator
    // im seeding with local machine time here, which doesnt give complete randomness but should be sufficient for this

    std::vector<float> test = LinSpace(1,5,5);
    for(const auto& e : test)
    {
        std::cout<<e<<' ';
    }
    std::cout<<std::endl;

}