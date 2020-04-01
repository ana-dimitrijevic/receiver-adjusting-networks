#pragma once
#include "Utils.h"
class PSO
{
public:
	double** swarm;
	int population_size, D, max;
	double** p_best;
	double g_best[2 * N] = { 0.0 };
	double** v;

	void initialise(double* swarm);
	void calculate_init_v(double* swarm);
	double** calculate_v(double** swarm, double** v, double** pBest, double* gBest, int x);
	double** calculate_x(double** swarm, double** v, int x);
	int optimisation_function(double* swarm);

	PSO();
};

