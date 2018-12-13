/*
 * BruteForce.hpp
 *
 *  Created on: 9 gru 2018
 *      Author: darek
 */

#ifndef BRUTEFORCE_HPP_
#define BRUTEFORCE_HPP_
#include "TSP.hpp"

class BruteForce: public TSP {
public:
	BruteForce(std::vector<std::vector<int>> adjacency_matrix);
	BruteForce(int** adjacency_matrix, int size);
	virtual ~BruteForce();

	void start();

private:
	void algorithm(int vertex_start);
};

#endif /* BRUTEFORCE_HPP_ */
