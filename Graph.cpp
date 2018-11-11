/*
 * Graph.cpp
 *
 *  Created on: 6 lis 2018
 *      Author: darek
 */

#include "Graph.hpp"

Graph::Graph(int matrix_size) :
		vertex_number(0), edge_number(0), algorithm_result_cost(-1) {
	if (vertex_number > 0)
		adjacency_matrix.reserve(matrix_size);
}

Graph::~Graph() {
	// TODO Auto-generated destructor stub
}

void Graph::addVertex() {
	std::vector<int> vec;
	for (int i = 0; i < vertex_number + 1; i++) {
		vec.push_back(-1);
	}
	for (int i = 0; i < vertex_number; i++) {
		adjacency_matrix[i].push_back(-1);
	}
	adjacency_matrix.push_back(vec);
	vertex_number++;
}

void Graph::setEdge(int begin, int end, int value) {
	if (begin > vertex_number || begin < 0) {
		throw RangeExceeded("Begin vertex is out of range!");
	}
	if (end > vertex_number || end < 0) {
		throw RangeExceeded("End vertex is out of range!");
	}
	if (begin == end) {
		throw RangeExceeded("Begin and end vertex is the same!");
	}
	if (value < -1) {
		throw RangeExceeded("Value is out of range!");
	}
	if (adjacency_matrix[begin][end] != value) {
		if (value == -1)
			edge_number--;
		else
			edge_number++;
	}
	adjacency_matrix[begin][end] = value;
}

void Graph::removeVertex(int vertex) {
	if (vertex > vertex_number || vertex < 0) {
		throw RangeExceeded("Vertex is out of range!");
	}
	for (int i = 0; i < vertex_number; i++) {
		adjacency_matrix[i].erase(adjacency_matrix[i].begin() + vertex);
	}
	adjacency_matrix.erase(adjacency_matrix.begin() + vertex);
	vertex_number--;
}

void Graph::removeEdge(int begin, int end) {
	setEdge(begin, end, -1);
}

int Graph::getVertexesNumber() {
	return vertex_number;
}

int Graph::getEdgesNumber() {
	return edge_number;
}

Path Graph::getResult() {
	return algorithm_result_path;
}

void Graph::loadFromFile(std::string filename) {
	std::fstream handle;
	handle.open(filename, std::ios::in);
	if (!handle.is_open())
		throw FileException("File isn't open!");

	Matrix result_adjacency_matrix;
	int result_vertex_number = 0;
	handle >> result_vertex_number;

	for (int i = 0; i < result_vertex_number; i++) {
		std::vector<int> vec;
		vec.reserve(result_vertex_number);
		int tmp_value = -1;
		for (int j = 0; j < result_vertex_number; j++) {
			handle >> tmp_value;
			vec.push_back(tmp_value);
		}
		result_adjacency_matrix.push_back(vec);
	}
	/*if (!checkIntegrity(result_adjacency_matrix))
	 throw FileException("File isn't valid!");*/

	vertex_number = result_vertex_number;
	adjacency_matrix = result_adjacency_matrix;
}

void Graph::saveToFile(std::string filename) {
	std::fstream handle;
	handle.open("." + filename + ".tmp", std::ios::out | std::ios::trunc);
	if (!handle.is_open())
		throw FileException("File isn't open!");
	handle << getVertexesNumber() << std::endl;
	handle << *this << std::endl;
}

void Graph::solveTSP() {
	TSP algorithm(adjacency_matrix);
	algorithm.bruteForce(0);
	algorithm_result_path = algorithm.getResultPath();
	algorithm_result_cost = algorithm.getResultCost();

	for (int i = 0; i < vertex_number; i++)
		std::cout << algorithm_result_path[i] << "->";
	std::cout << algorithm_result_path[vertex_number] << std::endl;
	std::cout << "Koszt = " << algorithm_result_cost << std::endl;
}

void Graph::print() {
	std::cout << *this;
}

std::vector<int>& Graph::operator [](uint index) {
	return adjacency_matrix[index];
}

std::ostream & operator <<(std::ostream & ostr, Graph & obj) {
	for (int i = 0; i < obj.getVertexesNumber(); i++) {
		for (int j = 0; j < obj.getVertexesNumber(); j++) {
			ostr << std::setw(3) << obj[i][j] << " ";
		}
		ostr << std::endl;
	}
	return ostr;
}

bool Graph::checkIntegrity(Matrix adjacency_matrix) {
	//TODO: sprawdzenie zgodności macierzy
	return true;
}
