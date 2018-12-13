/*
 * BranchAndBound.hpp
 *
 *  Created on: 9 gru 2018
 *      Author: darek
 */

#ifndef BRANCHANDBOUND_HPP_
#define BRANCHANDBOUND_HPP_
#include "TSP.hpp"

class BranchAndBound: public TSP {
public:
	BranchAndBound(std::vector<std::vector<int>> adjacency_matrix);
	BranchAndBound(int** adjacency_matrix, int size);
	virtual ~BranchAndBound();

	void start();

private:
	void algorithm();
};

#endif /* BRANCHANDBOUND_HPP_ */
