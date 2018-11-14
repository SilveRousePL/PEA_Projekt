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

void TSP::branchAndBound() {
	// Inicjowanie zmiennych do pracy z algorytmem B&B
	int** matrix = new int*[vertex_number + 1];
	for (int i = 0; i < vertex_number + 1; i++) {
		matrix[i] = new int[vertex_number + 1];
		for (int j = 0; j < vertex_number; j++) {
			if (i == j || i == vertex_number || j == vertex_number)
				matrix[i][j] = INT_MAX;
			else
				matrix[i][j] = adjacency_matrix[i][j];
		}
	}
	bool* active_row = new bool[vertex_number];
	bool* active_col = new bool[vertex_number];
	for (int i = 0; i < vertex_number; i++) {
		active_row[i] = true;
		active_col[i] = true;
	}
	active_row[vertex_number] = false;
	active_col[vertex_number] = false;

	std::vector<int> result_row;
	result_row.reserve(vertex_number);
	std::vector<int> result_col;
	result_col.reserve(vertex_number);

	// Główny algorytm
	for (int active_vertex_number = vertex_number; active_vertex_number >= 2;
			active_vertex_number--) {
		/*
		 * Od tego miejsca szukamy najmniejszych elementów w wierszach, kolumnach i odejmujemy je od reszty elementów zawartych w nich
		 */
		for (int i = 0; i < vertex_number; i++) {
			matrix[i][vertex_number] = INT_MAX;
			for (int j = 0; j < vertex_number; j++) {
				if (matrix[i][vertex_number] > matrix[i][j]
						&& matrix[i][j] != -1)
					matrix[i][vertex_number] = matrix[i][j];
			}
		}
		for (int i = 0; i < vertex_number; i++) {
			for (int j = 0; j < vertex_number; j++) {
				if (matrix[i][j] == INT_MAX || matrix[i][j] == -1)
					continue;
				matrix[i][j] -= matrix[i][vertex_number];
			}
		}
		for (int i = 0; i < vertex_number; i++) {
			matrix[vertex_number][i] = INT_MAX;
			for (int j = 0; j < vertex_number; j++) {
				if (matrix[vertex_number][i] > matrix[j][i]
						&& matrix[j][i] != -1)
					matrix[vertex_number][i] = matrix[j][i];
			}
		}
		for (int i = 0; i < vertex_number; i++) {
			for (int j = 0; j < vertex_number; j++) {
				if (matrix[j][i] == INT_MAX || matrix[j][i] == -1)
					continue;
				matrix[j][i] -= matrix[vertex_number][i];
			}
		}

		/*
		 * Jeśli uzyskaliśmy macierz 2x2 to przeskakujemy do czynności końcowych
		 */
		if (active_vertex_number == 2)
			break;

		/*
		 * Przeszukujemy każdy wiersz i kolumnę w poszukiwaniu najmniejszego elementu
		 * (Wartość zero jest pomijana w poszukiwaniach, uwzględnia się ją dopiero
		 * jak wystąpi co najmniej dwa razy)
		 */
		for (int i = 0; i < vertex_number; i++) {
			matrix[i][vertex_number] = INT_MAX;
			int count_zero_row = 0;
			for (int j = 0; j < vertex_number; j++) {
				if (matrix[i][vertex_number] > matrix[i][j]
						&& matrix[i][j] != -1 && matrix[i][j] != 0)
					matrix[i][vertex_number] = matrix[i][j];
				if (matrix[i][j] == 0)
					count_zero_row++;
			}
			if (count_zero_row > 1)
				matrix[i][vertex_number] = 0;
		}

		for (int i = 0; i < vertex_number; i++) {
			matrix[vertex_number][i] = INT_MAX;
			int count_zero_col = 0;
			for (int j = 0; j < vertex_number; j++) {
				if (matrix[vertex_number][i] > matrix[j][i]
						&& matrix[j][i] != -1 && matrix[j][i] != 0)
					matrix[vertex_number][i] = matrix[j][i];
				if (matrix[j][i] == 0)
					count_zero_col++;
			}
			if (count_zero_col > 1)
				matrix[vertex_number][i] = 0;
		}

		/*
		 * Z odnalezionych elementów wybieramy wartość posiadającą największy koszt
		 */
		int max_row_index = 0;
		int max_row_value = 0;
		for (int i = 0; i < vertex_number; i++) {
			if (matrix[i][vertex_number]
					> max_row_value&& matrix[i][vertex_number] != INT_MAX) {
				max_row_index = i;
				max_row_value = matrix[i][vertex_number];
			}
		}
		int max_col_index = 0;
		int max_col_value = 0;
		for (int i = 0; i < vertex_number; i++) {
			if (matrix[vertex_number][i]
					> max_col_value&& matrix[vertex_number][i] != INT_MAX) {
				max_col_index = i;
				max_col_value = matrix[vertex_number][i];
			}
		}

		/*
		 * I porównujemy czy wartość z kolumn jest największa czy z wierszy,
		 * a następnie dezaktywujemy (skracamy) w zależności wystąpienia największego
		 * z minimów kolumnę (wiersz) oraz wiersz (kolumnę), w którym w skracanej
		 * kolumnie (wierszu) wystąpiło zero
		 */
		if (max_row_value > max_col_value) {
			active_row[max_row_index] = false;
			for (int i = 0; i < vertex_number; i++) {
				if (matrix[max_row_index][i] == 0) {
					active_col[i] = false;
					max_col_index = i;
					break;
				}
			}
		} else {
			active_col[max_col_index] = false;
			for (int i = 0; i < vertex_number; i++) {
				if (matrix[i][max_col_index] == 0) {
					active_row[i] = false;
					max_row_index = i;
					break;
				}
			}
		}

		/*
		 * Blokujemy przejście powrotne poprzez wstawienie nieskończonego
		 * kosztu przejścia
		 */
		if (active_row[max_col_index] && active_col[max_row_index])
			matrix[max_col_index][max_row_index] = INT_MAX;

		result_row.push_back(max_row_index);
		result_col.push_back(max_col_index);

		for (int i = 0; i < vertex_number; i++) {
			matrix[max_row_index][i] = -1;
			matrix[i][max_col_index] = -1;
			matrix[i][vertex_number] = INT_MAX;
			matrix[vertex_number][i] = INT_MAX;
		}

		//DEBUG COUT
		std::cout << "      ";
		for (int i = 0; i < vertex_number; i++) {
			if (!active_col[i])
				continue;
			std::cout << std::setw(3) << i << " ";
		}
		std::cout << std::endl;
		for (int i = 0; i < vertex_number; i++) {
			if (!active_row[i])
				continue;
			std::cout << std::setw(4) << i << " | ";
			for (int j = 0; j < vertex_number; j++) {
				if (!active_col[j])
					continue;
				if (matrix[i][j] == INT_MAX) {
					std::cout << std::setw(3) << "INF";
				} else {
					std::cout << std::setw(3) << matrix[i][j];
				}
				std::cout << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "---------------------------------------------";
		std::cout << std::endl << std::endl;
	} //Koniec głównego algorytmu

	/*
	 * Czynności końcowe po osiągnięciu macierzy 2x2:
	 * Dodanie ostatnich dwóch wierzchołków do wyniku końcowego
	 */
	std::vector<std::vector<int>> tab;
	for (int i = 0; i < vertex_number; i++) {
		if (!active_row[i])
			continue;
		for (int j = 0; j < vertex_number; j++) {
			if (!active_col[j])
				continue;
			std::vector<int> tmp;
			tmp.push_back(i);
			tmp.push_back(j);
			tmp.push_back(matrix[i][j]);
			tab.push_back(tmp);
		}
	}
	for (int i = 0; i < tab.size(); i++) {
		if (tab[i][2] == INT_MAX) {
			if (i == 0 || i == 3) {
				result_row.push_back(tab[1][0]);
				result_col.push_back(tab[1][1]);
				result_row.push_back(tab[2][0]);
				result_col.push_back(tab[2][1]);
			} else {
				result_row.push_back(tab[0][0]);
				result_col.push_back(tab[0][1]);
				result_row.push_back(tab[3][0]);
				result_col.push_back(tab[3][1]);
			}
		}
	}

	std::cout << "ROW: ";
	for (int i = 0; i < vertex_number; i++) {
		std::cout << result_row[i] << " ";
	}
	std::cout << std::endl << "COL: ";
	for (int i = 0; i < vertex_number; i++) {
		std::cout << result_col[i] << " ";
	}
	std::cout << std::endl << std::endl;

	result_path.clear();
	result_path.push_back(0);
	for (int i = 0; i < vertex_number; i++) {
		for (int j = 0; j < vertex_number; j++) {
			if (result_row[j] == result_path.back()) {
				result_path.push_back(result_col[j]);
				break;
			}
		}
	}

	result_cost = 0;
	for (int i = 0; i < vertex_number - 1; i++)
		result_cost += adjacency_matrix[result_path[i]][result_path[i + 1]];
	result_cost +=
			adjacency_matrix[result_path[vertex_number - 1]][result_path[0]];
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
