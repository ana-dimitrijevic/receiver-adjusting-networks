#define _USE_MATH_DEFINES
#include "defs.h"
#include "Utils.h"
#include "PSO.h"
#include <time.h>
#include <iostream>

PSO pso = PSO();

void print_results() {

	std::cout << "IOA Ispitni zadatak januar 2019.";
	std::cout << std::endl;
	std::cout << "Ana Dimtitrijevic 2016/0442";
	std::cout << std::endl;
	std::cout << "*******************************************";
	std::cout << std::endl;
	std::cout << "Zc : (";
	std::cout << pso.g_best[0];
	std::cout << " ";
	for (int i = 1; i < 2 * N; i++) {
		if (i % 2 == 0) {
			std::cout << pso.g_best[i];
			std::cout << " ";
		}
	}
	std::cout << ") [Ohm]";
	std::cout << std::endl;

	std::cout << "l : (";
	std::cout << pso.g_best[1];
	std::cout << " ";
	for (int i = 2; i < 2 * N; i++) {
		if (i % 2 == 1) {
			std::cout << pso.g_best[i];
			std::cout << " ";
		}	
	}
	std::cout << ") [m]";
	std::cout << std::endl;

	std::cout << "Max : ";
	std::cout << pso.max;
	std::cout << std::endl;
	std::cout << "*******************************************";
}

void init_PSO() { 
	srand(time(0));
}

void update_g_best(int result, int x) {

	pso.max = result;
	for (int i = 0; i < 2 * N; i++)
		pso.g_best[i] = pso.swarm[x][i];

}

void update_p_best(int x) {

	for (int i = 0; i < 2 * N; i++)
		pso.p_best[x][i] = pso.swarm[x][i];

}

void main() {

	init_PSO();
	
	for (int i = 0; i < number_of_iterations; i++) {
		for (int x = 0; x < pso.population_size; x++) {

			int result = pso.optimisation_function(pso.swarm[x]);

			if (pso.max < result) {
				update_g_best(result, x);
			}
			if (result > pso.optimisation_function(pso.p_best[x])) {
				update_p_best(x);
			}

			pso.v = pso.calculate_v(pso.swarm, pso.v, pso.p_best, pso.g_best, x);
			pso.swarm = pso.calculate_x(pso.swarm, pso.v, x);
		}
	}

	print_results();

}