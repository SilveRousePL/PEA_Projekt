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
#include <vector>
#include "TSP.hpp"
#include "Exception.hpp"

typedef std::vector<std::vector<int>> Matrix;
typedef std::vector<int> Path;

class Graph {
	Matrix adjacency_matrix;
	int vertex_number;
	int edge_number;
	std::string filename;
	Path algorithm_result_path;
	int algorithm_result_cost;

public:
	Graph(int matrix_size = 0);
	virtual ~Graph();

	void addVertex();
	void setEdge(int begin, int end, int value);
	void removeVertex(int vertex);
	void removeEdge(int begin, int end);

	int getVertexNumber();
	int getEdgesNumber();
	Path getResult();
	std::string getFilename();

	void loadFromFile(std::string filename);
	void saveToFile(std::string filename);

	void solveTSP_BF();
	void solveTSP_BB();

	void print();

	std::vector<int>& operator [](uint index);
	friend std::ostream & operator <<(std::ostream & ostr, Graph & obj);

private:
	bool checkIntegrity(Matrix adjacency_matrix);
};

#endif /* GRAPH_HPP_ */
