#pragma once
#define _USE_MATH_DEFINES
#include <cmath>  
#include <complex>
#include "defs.h"
#include "PSO.h"
class Utils {
public:
	static double generate_random_value(double min, double max);
	static double generate_beta(double f);
	static std::complex<double> generate_z_out(std::complex<double> zin, double zc, double beta, double l);
};

