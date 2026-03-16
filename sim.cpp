#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>

// Real world consts
const float M = 1.00784*1.66*pow(10,-27); //[kg] //using atomic mass of H
const float k_B = 1.380649*pow(10, -23); //boltzmann const

float PotentialSinSqr(float x, float t, float A, float k, float omega, float phi)
{
    /*
    Simple U = A sin^2{kx + omega t + phi} potential
    takes in all variables and returns a float of the potential in joules
    x expected in metres, time in s, omega in rad/s, A in joules, k in rad/m, phi in rad
    */
   return A*std::pow(std::sin((k*x) + (omega * t) + phi),2)
}
float ForceSinSqr(float x, float t, float A, float k, float omega, float phi)
{
    /*
    F = - dU/dx, so F = -kA sin(2[kx * omega t + phi])
    takes in all variables and returns a float of the potential in joules
    x expected in metres, time in s, omega in rad/s, A in joules, k in rad/m, phi in rad
    */
   return k*a*std::sin(2((k*x)+(omega*t)+phi));
}