// No AI used in the making of this im a real one 
// I get things abhorently wrong the old fasioned way
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

// Maxwell Boltzman shit
float MaxBoltCDF(float v, float T, float offset = 0)
{
    /*
    Returns the cdf value for the maxwell-boltzman distribution for a temp T and a vel v
    Assuming a const mass defined at the top of the program.
    This can also be offset if needed (eg if tryna a velocity numerically using a numerical
    method that finds roots)
    */
    float a = pow((k_B*T)/M,0.5);
    return -offset + std::erf(v/(pow(2,0.5)*a)) - pow(2/M_PI,0.5)*(v/a)*std::exp(-(pow(v,2)/(2*pow(a,2))));
}
float MaxBoltPDF(float v, float T)
{
    /*
    returns pdf of maxwell boltz dist -> derivative of cdf (hint hint newton raphson)
    */
    float a = pow((k_B*T)/M,0.5);
    return pow(2/M_PI, 0.5) * (pow(v,2)/pow(a,3)) * std::exp(-(pow(v,2)/(2*pow(a,2))));
}

//Numerical method
float NewtonRaphsonMaxBolt(float y, int N, float T, float (*func)(float, float, float), float (*deriv)(float, float), float guess = 0)
{
    /*
    uses the newton raphon method to solve for the velocity in the inverse CDF of the
    maxwell boltzman distribution, for N iterations using a uniform random 
    variable y [0,1), at a temperature T. An initial guess is optional.

    NOTE if guess = 0 then this breaks for maxboltcdf so its set to the temp/ke conversion
    velocity
    */
    if(guess == 0)
    {
        guess = pow((2*k_B*T)/M, 0.5);
    }
    float x_i = guess - func(guess, T, y)/deriv(guess,T);
    for(int i = 0; i < N-1; i++)
    {
        x_i = x_i - func(x_i, T, y)/deriv(guess,T);
    }
    return x_i;
}

// main
int main()
{
    std::srand(time(0)); // seed uniform random num generator
    // im seeding with local machine time here, which doesnt give complete randomness but should be sufficient for this

    float root = NewtonRaphsonMaxBolt(0, 10, 0.001, MaxBoltCDF, MaxBoltPDF);
    std::cout<<root<<std::endl;

    std::cout<<MaxBoltCDF(root,0.001)<<std::endl;

}