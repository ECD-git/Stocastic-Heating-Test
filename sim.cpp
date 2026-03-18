// No AI used in the making of this im a real one 
// I get things abhorently wrong the old fasioned way
#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>

// Real world consts
const float M = 1.00784*1.66*pow(10,-27); //[kg] //using atomic mass of H
const float k_B = 1.380649*pow(10, -23); //boltzmann const

// Useful functions
float KelToE(float kel)
{
    // converts E=k_BT
    return k_B*kel;
}

// Random Functions
float RandomFloat(float min, float max)
{
    // generates a random float between a range min and max
    return min + static_cast <float> (std::rand()) / (static_cast <float> (RAND_MAX/(max-min)));
}
std::vector<float> RandomUnitVector()
{
    /*
    Returns a 3vector with a magnitude of 1, pointing in a random dir
    */
    // use polar coords for most uniform spherical dist
    float theta = RandomFloat(0, M_PI);
    float phi = RandomFloat(0, 2*M_PI);
    std::vector<float> i_hat{{std::sin(theta)*std::cos(phi),std::sin(theta)*std::sin(phi),std::cos(theta)}};
    return i_hat;
}

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
std::vector<float> RandLinSpace(int N, float min=0.0, float max=1.0)
{
    /*
    Generates a vector of N elements, uniformly randomly generated between min and max
    */
    std::vector<float> vec(N);
    std::generate(vec.begin(), vec.end(), [&min, &max] () {return RandomFloat(min, max);});
    return vec;
}
std::vector<std::vector<float>> RandUnitVecSpace(int N)
{
    std::vector<std::vector<float>> vec(N, std::vector<float>(3));
    std::generate(vec.begin(), vec.end(), [] () {return RandomUnitVector();});
    return vec;
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
float MaxBoltCDF(float v, float T, float U)
{
    /*
    Returns the cdf value for the maxwell-boltzman distribution for a temp T and a vel v in potential U
    Assuming a const mass defined at the top of the program.
    This can also be offset if needed (eg if tryna a velocity numerically using a numerical
    method that finds roots)
    */
    float E = (0.5*M*pow(v,2))+U;
    return std::erf( pow(E/(k_B*T),0.5) ) - (2/pow(M_PI,0.5))* pow(E/(k_B*T),0.5) * std::exp(-E/(k_B*T));
}
float MaxBoltPDF(float v, float T, float U)
{
    /*
    returns pdf of maxwell boltz dist -> derivative of cdf (hint hint newton raphson)
    */
    float E = (0.5*M*pow(v,2))+U;
    return pow(2/M_PI,0.5) * 2 * pow(M/(k_B*T),0.5) * (E/(k_B*T)) * std::exp(-E/(k_B*T));
}

//Numerical methods
float NewtonRaphsonMaxBolt(float y, float U, float T, int N, float (*func)(float, float, float), float (*deriv)(float, float, float), float guess = 0)
{
    
    //uses the newton raphon method to solve for the velocity in the inverse CDF of the
    //maxwell boltzman distribution, for N iterations using a uniform random 
    //variable y [0,1), at a temperature T. An initial guess is optional.

    //NOTE if guess = 0 then this breaks for maxboltcdf so its set to the temp/ke conversion
    //velocity
    
    if(guess == 0)
    { // the deriv at 0 is undefined so if 0 is given then use KE = k_bT as guess
        guess = pow((2*k_B*T)/M, 0.5);
    }
    float x_i = guess - (func(guess, T, U)-y)/deriv(guess, T, U);
    for(int i = 0; i < N-1; i++)
    {
        x_i = x_i - (func(x_i, T, U)-y)/deriv(guess,T,U);
    }
    return x_i;
}

// Vector Processes

float VectorMagnitude(const std::vector<float>& vector)
{
    float magnitude = 0;
    for (const auto& i : vector)
    {
        magnitude += pow(i,2);
    }
    return pow(magnitude,0.5);
}
void ScaleVector(std::vector<float>& vec, float scale)
{
    std::transform(vec.begin(), vec.end(), vec.begin(), [&scale](float i){return i*scale;});
}

//Tests
void RandSphereDist(float N)
{
    // Pulls N random unit vectors and outputs them for plotting
    std::ofstream result;
    result.open("randsphere.dat");
    for (auto& comp : RandUnitVecSpace(N))
    {
        for (auto& i : comp)
        {
            result<<i<<',';
        }
        result<<'\n';
    }
    result.close();
}
void MaxBoltHistTest(float N, float U, float T)
{
    // pulls N random velocities from our max bolt dist for plotting
    std::ofstream result;
    result.open("mbhisttest.dat");
    std::vector<float> data(N);
    std::generate(data.begin(), data.end(),  [&U, &T] () {return NewtonRaphsonMaxBolt(RandomFloat(0,1),U,T,5,MaxBoltCDF,MaxBoltPDF);});
    result<<U<<'\n'<<T<<'\n';
    for (float& i : data)
    {
        result<<i<<'\n';
    }
    result.close();
}

// main
int main()
{
    std::srand(time(0)); // seed uniform random num generator
    // im seeding with local machine time here, which doesnt give complete randomness but should be sufficient for this
    // Tests
    //RandSphereDist(1000);
    MaxBoltHistTest(10000, 0, 0.005);
}