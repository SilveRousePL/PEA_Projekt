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

class TSP {
	int** adjacency_matrix;
	int vertex_number;
	std::vector<int> result_path;
	int result_cost;

public:
	TSP(std::vector<std::vector<int>> adjacency_matrix);
	virtual ~TSP();

	void bruteForce(int vertex_start);
	void branchAndBound();

	std::vector<int> getResultPath();
	int getResultCost();

private:
	void convertToArray(std::vector<std::vector<int>> vec);
	bool nextPermutation(int* begin, int* end);
};

#endif /* TSP_HPP_ */
