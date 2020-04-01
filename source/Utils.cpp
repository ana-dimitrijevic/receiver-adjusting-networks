#include "Utils.h"
using namespace std;

double Utils::generate_random_value(double min, double max) {
	return min + ((double)rand() / RAND_MAX) * (max - min);
}

double Utils::generate_beta(double f) {
	return (2.0 * M_PI * f) / c0;
}

complex<double> Utils::generate_z_out(complex<double> zin, double zc, double beta, double l) {

	complex<double> comp1, comp2;
	
	comp1.imag(zc * tan(beta * l / 1000));
	comp2.real((-1.00) * zin.imag() * tan(beta * l / 1000));
	comp2.imag(zin.real() * tan(beta * l / 1000));

	return zc * ((zin + comp1) / (zc + comp2));
}
