/*
 * TSP.cpp
 *
 *  Created on: 30 paź 2018
 *      Author: darek
 */

#include "TSP.hpp"

TSP::TSP(std::vector<std::vector<int>> adjacency_matrix) :
		adjacency_matrix(new int*[adjacency_matrix.size()]), vertex_number(
				adjacency_matrix.size()), result_cost(-1) {
	for (int i = 0; i < vertex_number; i++) {
		this->adjacency_matrix[i] = new int[vertex_number];
		for (int j = 0; j < vertex_number; j++) {
			this->adjacency_matrix[i][j] = adjacency_matrix[i][j];
		}
	}
}

TSP::TSP(int** adjacency_matrix, int size) :
		adjacency_matrix(new int*[size]), vertex_number(size), result_cost(-1) {
	for (int i = 0; i < vertex_number; i++) {
		this->adjacency_matrix[i] = new int[vertex_number];
		for (int j = 0; j < vertex_number; j++) {
			this->adjacency_matrix[i][j] = adjacency_matrix[i][j];
		}
	}
}

TSP::~TSP() {
	for (int i = 0; i < vertex_number; i++) {
		delete[] adjacency_matrix[i];
	}
	delete[] adjacency_matrix;
}

std::vector<int> TSP::getResultPath() {
	return result_path;
}

int TSP::getResultCost() {
	calcCost(result_path);
	return result_cost;
}

int TSP::calcCost(std::vector<int>& path) {
	if (path.size() <= 1)
		return -1;
	int cost = 0;
	for (int i = 0; i != path.size() - 1; i++)
		cost += adjacency_matrix[path[i]][path[i + 1]];
	return cost;
}

bool TSP::nextPermutation(int* begin, int* end) { //Działa szybciej niż z STL-a
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
