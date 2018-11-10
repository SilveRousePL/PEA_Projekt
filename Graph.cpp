/*
 * Graph.cpp
 *
 *  Created on: 6 lis 2018
 *      Author: darek
 */

#include "Graph.hpp"

Graph::Graph(int matrix_size) :
		vertexes_number(0), edges_number(0) {
	if (vertexes_number > 0)
		adjacency_matrix.reserve(matrix_size);
}

Graph::~Graph() {
	// TODO Auto-generated destructor stub
}

void Graph::addVertex() {
	std::vector<int> vec;
	for (int i = 0; i < vertexes_number + 1; i++) {
		vec.push_back(-1);
	}
	adjacency_matrix.push_back(vec);
	vertexes_number++;
}

void Graph::setEdge(int begin, int end, int value) {
	if (begin > vertexes_number || begin < 0) {
		throw RangeExceeded("Begin vertex is out of range!");
	}
	if (end > vertexes_number || end < 0) {
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
			edges_number--;
		else
			edges_number++;
	}
	adjacency_matrix[begin][end] = value;
}

void Graph::removeVertex(int vertex) { //Wszystko powyżej wartości iteratora się przesuwa, więc trzeba przesunąć resztę danych o ileś (chyba)
	if (vertex > vertexes_number || vertex < 0) {
		throw RangeExceeded("Vertex is out of range!");
	}
	for (int i = 0; i < vertexes_number; i++) {
		removeEdge(vertex, i);
		removeEdge(i, vertex);
		adjacency_matrix[i].erase(adjacency_matrix[i].begin() + vertex);
	}
	adjacency_matrix.erase(adjacency_matrix.begin() + vertex);
}

void Graph::removeEdge(int begin, int end) {
	setEdge(begin, end, -1);
}

int Graph::getVertexesNumber() {
	return vertexes_number;
}

int Graph::getEdgesNumber() {
	return edges_number;
}

Path Graph::getResult() {
	return algorithm_result;
}

int Graph::getResultLength() {
	int res = 0;
	for(auto it=algorithm_result.begin(); it<algorithm_result.end()-1; it++) {
		res += adjacency_matrix[*it][*it+1];
	}
	return res;
}

void Graph::loadFromFile(std::string filename) {
	std::fstream handle;
	handle.open(filename, std::ios::in);
	if (!handle.is_open())
		throw FileException("File isn't open!");

	std::vector<std::vector<int>> result_adjacency_matrix;
	int result_vertex_number = 0;
	handle >> result_vertex_number;

	for (int i = 0; i < result_vertex_number; i++) {
		std::vector<int> vec;
		std::string tmp_str;
		std::stringstream tmp_ss;
		int tmp_value;
		getline(handle, tmp_str);
		tmp_ss << tmp_str;
		vec.reserve(result_vertex_number);
		for (int j = 0; j < result_vertex_number; j++) {
			tmp_ss >> tmp_value;
			vec.push_back(tmp_value);
		}
		result_adjacency_matrix.push_back(vec);
	}
	if (!checkIntegrity(result_adjacency_matrix))
		throw FileException("File isn't valid!");
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
	algorithm_result = algorithm.getResult();
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
			ostr << obj[i][j] << " ";
		}
		ostr << std::endl;
	}
	return ostr;
}

bool Graph::checkIntegrity(Matrix adjacency_matrix) {
	//TODO: sprawdzenie zgodności macierzy
	return true;
}
