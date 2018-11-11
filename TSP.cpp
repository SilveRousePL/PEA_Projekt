/*
 * TSP.cpp
 *
 *  Created on: 30 paź 2018
 *      Author: darek
 */

#include "TSP.hpp"

TSP::TSP(std::vector<std::vector<int>> adjacency_matrix) :
		vertex_number(adjacency_matrix.size()) {
	convertToArray(adjacency_matrix);
}

TSP::~TSP() {
	for (int i = 0; i < vertex_number; i++) {
		delete[] adjacency_matrix[i];
	}
	delete[] adjacency_matrix;
}

void TSP::bruteForce(int vertex_start) {
	int* vertex_array = new int[vertex_number];
	int* result_array = new int[vertex_number];
	int min_cost = INT_MAX;
	vertex_array[0] = vertex_start;
	for (int i = 1; i < vertex_number; i++) {
		if (i > vertex_start)
			vertex_array[i] = i;
		else
			vertex_array[i] = i - 1;
	}
	for (int i = 0; i < vertex_number; i++)
		result_array[i] = -1;

	do {
		int total_cost = 0;
		for (int i = 0; i < vertex_number - 1; i++)
			total_cost +=
					adjacency_matrix[vertex_array[i]][vertex_array[i + 1]];
		total_cost +=
				adjacency_matrix[vertex_array[vertex_number - 1]][vertex_array[0]];

		if (total_cost < min_cost) {
			min_cost = total_cost;
			for (int j = 0; j < vertex_number; ++j)
				result_array[j] = vertex_array[j];
		}
		nextPermutation(vertex_array, vertex_array + vertex_number);
	} while (vertex_array[0] == vertex_start);

	for (int i = 0; i < vertex_number; i++) {
		result_path.push_back(result_array[i]);
	}
	result_path.push_back(result_array[0]);
	result_cost = min_cost;
}

int* TSP::branchAndBound() {

}

std::vector<int> TSP::getResultPath() {
	return result_path;
}

int TSP::getResultCost() {
	return result_cost;
}

void TSP::convertToArray(std::vector<std::vector<int>> vec) {
	adjacency_matrix = new int*[vertex_number];
	for (int i = 0; i < vertex_number; i++) {
		adjacency_matrix[i] = new int[vertex_number];
		for (int j = 0; j < vertex_number; j++) {
			adjacency_matrix[i][j] = vec[i][j];
		}
	}
}

bool TSP::nextPermutation(int* begin, int* end) {
	if (begin == end)
		return false;
	int* i = begin + 1;
	if (i == end)
		return false;
	i = end - 1;
	while (true) {
		int* j = i;
		i--;

		if (*i < *j) {
			int* k = end;
			while (!(*i < *--k))
				;
			std::swap(*i, *k);
			std::reverse(j, end);
			return true;
		}
		if (i == begin) {
			std::reverse(begin, end);
			return false;
		}
	}
}
