#include "PSO.h"

using namespace std;

PSO::PSO() {

	D = N * 2;
	population_size = 10 * D;
	max = 0;

	swarm = new double* [population_size];
	p_best = new double* [population_size];
	v = new double* [population_size];

	for (int i = 0; i < population_size; i++) {
		swarm[i] = new double[2 * N];
		initialise(swarm[i]);
	}

	for (int i = 0; i < population_size; i++) {
		p_best[i] = new double[2 * N];
		for (int j = 0; j < 2 * N; j++)
			p_best[i][j] = swarm[i][j];
	}

	for (int i = 0; i < population_size; i++) {
		v[i] = new double[2 * N];
		calculate_init_v(v[i]);
	}
}

void PSO::initialise(double* swarm) {
	for (int i = 0; i < 2 * N; i++) {
		i % 2 == 0 ? swarm[i] = Utils::generate_random_value(z_minimum, z_maximum) : swarm[i] = Utils::generate_random_value(l_minimum, l_maximum);
	}
}
void PSO::calculate_init_v(double* swarm) {
	for (int i = 0; i < 2 * N; i++) {
		swarm[i] = Utils::generate_random_value(0, v_max);
	}
}

double** PSO::calculate_v(double** swarm, double** v, double** pBest, double* gBest, int x) {

	for (int i = 0; i < 2 * N; i++) {
		v[x][i] = w * v[x][i] + c1 * (rand() / ((double)RAND_MAX)) * (pBest[x][i] - swarm[x][i]) + c2 * (rand() / ((double)RAND_MAX)) * (gBest[i] - swarm[x][i]);
		if (v[x][i] > v_max) v[x][i] = v_max;
	}
	return v;
}

double** PSO::calculate_x(double** swarm, double** v, int x) {

	for (int i = 0; i < 2 * N; i=i+2) {
		swarm[x][i] = swarm[x][i] + dT * v[x][i];
		swarm[x][i + 1] = swarm[x][i + 1] + dT * v[x][i + 1];

		if ((swarm[x][i] > z_maximum)) swarm[x][i] = z_maximum;
		if ((swarm[x][i] < z_minimum)) swarm[x][i] = z_minimum;
		if ((swarm[x][i+1] > l_maximum)) swarm[x][i+1] = l_maximum;
		if ((swarm[x][i+1] < l_minimum)) swarm[x][i+1] = l_minimum;
	}

	return swarm;
}

int PSO::optimisation_function(double* swarm) {
	double sum = 0;

	for (int f = f_minimum; f <= f_maximum; f += f_increment) {

		complex<double> zin;
		zin.real(100.0);
		zin.imag(-100.0);

		for (int i = 0; i < N * 2; i+=2) {
			complex<double> zout = Utils::generate_z_out(zin, swarm[i], Utils::generate_beta(f * 1000000), swarm[i + 1]);
			zin = zout;
		}

		double ro = 20.00 * log10(abs((zin - (double)z0) / (zin + (double)z0)));
		if (ro < ro_boundary) sum++;

	}

	return sum;
}