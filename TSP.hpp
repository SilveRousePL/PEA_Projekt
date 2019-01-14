/*
 * TSP.hpp
 *
 *  Created on: 30 paź 2018
 *      Author: darek
 */

#ifndef TSP_HPP_
#define TSP_HPP_
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <bits/stdc++.h>
#define debug true

enum TSP_algorithm {
	BRUTEFORCE, BRANCH_AND_BOUND, SIMULATED_ANNEALING, GENETIC
};

class TSP {
protected:
	int** adjacency_matrix;
	int vertex_number;
	std::vector<int> result_path;
	int result_cost;

public:
	TSP(std::vector<std::vector<int>> adjacency_matrix);
	TSP(int** adjacency_matrix, int size);
	virtual ~TSP();

	virtual void start() = 0;

	std::vector<int> getResultPath();
	int getResultCost();
	int calcCost(const std::vector<int>& path);
	int calcCostWithBeginAndEnd(const std::vector<int>& path);
	std::vector<int> randomSolution(int number);

protected:
	bool nextPermutation(int* begin, int* end);
};

#endif /* TSP_HPP_ */
