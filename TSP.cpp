/*
 * TSP.cpp
 *
 *  Created on: 30 paź 2018
 *      Author: darek
 */

#include "TSP.hpp"

TSP::TSP(std::vector<std::vector<int>> adjacency_matrix) :
		vertexes_number(adjacency_matrix.size()) {
	convertToArray(adjacency_matrix);

	v0 = 0;
	d = INF;
	dh = 0;
	sptr = 0;
	shptr = 0;

	S.reserve(vertexes_number);
	Sh.reserve(vertexes_number);

	visited = new bool[vertexes_number];
	/*A = new std::unique_ptr<bool>[vertexes_number];
	 W = new std::unique_ptr<int>[vertexes_number];
	 for (int i = 0; i < vertexes_number; i++) {
	 A[i] = new bool[vertexes_number];
	 W[i] = new int[vertexes_number];
	 for (int j = 0; j < vertexes_number; j++) {
	 A[i][j] = false;
	 W[i][j] = 0;
	 }
	 visited[i] = false;
	 }

	 // Odczytujemy dane wejściowe
	 for (i = 0; i < m; i++) {
	 std::cin >> x >> y >> z;
	 A[x][y] = A[y][x] = true;     // Krawędź x-y
	 W[x][y] = W[y][x] = z;     // Waga krawędzi x-y
	 }

	 std::cout << std::endl;*/

	// Rozpoczynamy algorytm
	start(v0);
	if (sptr) {
		for (int i = 0; i < sptr; i++)
			std::cout << S[i] << " ";
		std::cout << v0 << std::endl;
		std::cout << "d = " << d << std::endl;
	} else
		std::cout << "NO HAMILTONIAN CYCLE" << std::endl;

	std::cout << std::endl;

}

TSP::~TSP() {
}

void TSP::start(int v) {
	int u;

	Sh[shptr++] = v;              // zapamiętujemy na stosie bieżący wierzchołek

	if (shptr < vertexes_number) // jeśli brak ścieżki Hamiltona, to jej szukamy
			{
		visited[v] = true;      // Oznaczamy bieżący wierzchołek jako odwiedzony
		for (u = 0; u < vertexes_number; u++) // Przeglądamy sąsiadów wierzchołka v
			if (A[v][u] && !visited[u]) // Szukamy nieodwiedzonego jeszcze sąsiada
					{
				dh += W[v][u];            // Dodajemy wagę krawędzi v-u do sumy
				start(u);   // Rekurencyjnie wywołujemy szukanie cyklu Hamiltona
				dh -= W[v][u];            // Usuwamy wagę krawędzi z sumy
			}
		visited[v] = false;           // Zwalniamy bieżący wierzchołek
	} else if (A[v0][v]) {     // Jeśli znaleziona ścieżka jest cyklem Hamiltona
		dh += W[v][v0];            // to sprawdzamy, czy ma najmniejszą sumę wag
		if (dh < d)                    // Jeśli tak,
				{
			d = dh;                     // To zapamiętujemy tę sumę
			for (u = 0; u < shptr; u++)  // oraz kopiujemy stos Sh do S
				S[u] = Sh[u];
			sptr = shptr;
		}
		dh -= W[v][v0];               // Usuwamy wagę krawędzi v-v0 z sumy
	}
	shptr--;                        // Usuwamy bieżący wierzchołek ze ścieżki

}

std::vector<int> TSP::getResult() {
	return result;
}

void TSP::convertToArray(std::vector<std::vector<int>> vec) {
	adjacency_matrix = new int*[vertexes_number];
	for (int i = 0; i < vertexes_number; i++) {
		adjacency_matrix[i] = new int[vertexes_number];
		for (int j = 0; j < vertexes_number; j++) {
			adjacency_matrix[i][j] = vec[i][j];
		}
	}
}
