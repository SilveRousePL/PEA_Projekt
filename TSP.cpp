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

int TSP::calcCost(const std::vector<int>& path) {
	if (path.size() <= 1)
		return -1;
	int cost = 0;
	for (int i = 0; i != path.size() - 1; i++)
		cost += adjacency_matrix[path[i]][path[i + 1]];
	return cost;
}

int TSP::calcCostWithBeginAndEnd(const std::vector<int>& path) {
	int result = calcCost(path);
	if (result != -1)
		result += adjacency_matrix[path[path.size() - 1]][path[0]];
	return result;
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

std::vector<int> TSP::randomSolution(int number) {
	int* tab_i = new int[number];
	std::vector<int> res;
	for (int i = 0; i < number; ++i)
		tab_i[i] = i;

	for (int i = 0; i < number; ++i) {
		int x = rand() % number;
		if (tab_i[x] == -1) {
			--i;
			continue;
		}
		res.push_back(tab_i[x]);
		tab_i[x] = -1;
	}
	res.push_back(res[0]);
	delete[] tab_i;
	return res;
}
