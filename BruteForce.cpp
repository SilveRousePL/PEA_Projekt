/*
 * BruteForce.cpp
 *
 *  Created on: 9 gru 2018
 *      Author: darek
 */

#include "BruteForce.hpp"

BruteForce::BruteForce(std::vector<std::vector<int>> adjacency_matrix) :
		TSP(adjacency_matrix) {
}

BruteForce::BruteForce(int** adjacency_matrix, int size) :
		TSP(adjacency_matrix, size) {
}

BruteForce::~BruteForce() {
}

void BruteForce::start() {
	this->algorithm(0);
}

void BruteForce::algorithm(int vertex_start) {
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
