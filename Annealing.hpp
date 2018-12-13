/*
 * Annealing.hpp
 *
 *  Created on: 9 gru 2018
 *      Author: darek
 */

#ifndef ANNEALING_HPP_
#define ANNEALING_HPP_
#include "TSP.hpp"

//Simulated Annealing
class Annealing: public TSP {
	int begin_temperature;
	double temperature_change_factor;
	double worse_acceptable_factor;

public:
	Annealing(std::vector<std::vector<int>> adjacency_matrix);
	Annealing(int** adjacency_matrix, int size);
	virtual ~Annealing();

	void start();
	void enterParam(int beg_temp, double temp_change_factor,
			double worse_accept_factor);

private:
	std::vector<int> algorithm();
	std::vector<int> randomSolution(int number);
	std::vector<int> adjacentSolution(std::vector<int> res);
};

#endif /* ANNEALING_HPP_ */
