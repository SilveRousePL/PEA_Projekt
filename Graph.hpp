/*
 * Graph.hpp
 *
 *  Created on: 6 lis 2018
 *      Author: darek
 */

#ifndef GRAPH_HPP_
#define GRAPH_HPP_
#include <iostream>
#include <fstream>
#include <memory>
#include "Timer.hpp"
#include "BruteForce.hpp"
#include "BranchAndBound.hpp"
#include "Annealing.hpp"
#include "Exception.hpp"

typedef std::vector<std::vector<int>> Matrix;
typedef std::vector<int> Path;

class Graph: public Timer {
	Matrix adjacency_matrix;
	int vertex_number;
	int edge_number;
	std::string filename;

public:
	Graph(int matrix_size = 0);
	virtual ~Graph();

	void addVertex();
	void setEdge(int begin, int end, int value);
	void removeVertex(int vertex);
	void removeEdge(int begin, int end);

	int getVertexNumber();
	int getEdgesNumber();
	std::string getFilename();

	void loadFromFile(std::string filename);
	void saveToFile(std::string filename);

	void solveTSP(TSP_algorithm alg);
	void annealingTest();

	void print();

	std::vector<int>& operator [](uint index);
	friend std::ostream & operator <<(std::ostream & ostr, Graph & obj);

private:
	bool checkIntegrity(Matrix adjacency_matrix);
};

#endif /* GRAPH_HPP_ */
