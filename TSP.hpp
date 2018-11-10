/*
 * TSP.hpp
 *
 *  Created on: 30 paź 2018
 *      Author: darek
 */

#ifndef TSP_HPP_
#define TSP_HPP_
#include <iostream>
#include <array>
#include <vector>
#include <memory>
#include "Graph.hpp"

const int INF = 2147483647;

class TSP {
	int vertexes_number;
	int v0;
	int d;
	int dh;
	int sptr;
	int shptr;

	bool** A;	// Macierz sąsiedztwa
	int** W;	// Macierz wag krawędzi

	int** adjacency_matrix;	// Macierz sąsiedztwa

	std::vector<int> S;							// Stos w tablicy
	std::vector<int> Sh;						// Stos w tablicy
	bool* visited;				// Tablica odwiedzin

	std::vector<int> result;

public:
	TSP(std::vector<std::vector<int>> adjacency_matrix);
	virtual ~TSP();

	void start(int v);
	std::vector<int> getResult();

private:
	void convertToArray(std::vector<std::vector<int>> vec);
};

#endif /* TSP_HPP_ */
