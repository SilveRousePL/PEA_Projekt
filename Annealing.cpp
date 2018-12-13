/*
 * Annealing.cpp
 *
 *  Created on: 9 gru 2018
 *      Author: darek
 */

#include "Annealing.hpp"

Annealing::Annealing(std::vector<std::vector<int>> adjacency_matrix) :
		TSP(adjacency_matrix), begin_temperature(500), temperature_change_factor(
				0.99), worse_acceptable_factor(10) {
}

Annealing::Annealing(int** adjacency_matrix, int size) :
		TSP(adjacency_matrix, size), begin_temperature(500), temperature_change_factor(
				0.99), worse_acceptable_factor(10) {
}

Annealing::~Annealing() {
}

void Annealing::start() {
	this->result_path = this->algorithm();
	this->result_cost = calcCost(this->result_path);
}

std::vector<int> Annealing::algorithm() {
	//std::fstream file("AnnealingOneMeasure.txt", std::ios::out | std::ios::trunc);
	int worse_solution_counter = 0; // Licznik znalezionych gorszych rozwiazań
	int worse_acceptable = worse_acceptable_factor * vertex_number; // Akceptowalna liczba wyszukań gorszych rozwiązań pod rząd
	double temperature = begin_temperature; // Przypisanie początkowej temperatury
	std::vector<int> current_solution = randomSolution(vertex_number); // Losowanie pierwszego rozwiązania i przypisanie go jako rozwiązanie obecne
	std::vector<int> best_solution = current_solution; // Wylosowane rozwiązanie jest automatycznie najlepszym, ponieważ jest to jedyne rozwiązanie
	std::vector<int> adjacent_solution = current_solution; // Przypisanie obecnego rozwiązania jako sąsiedniego celem wykonania operacji na nim
	int cost_current_solution, cost_best_solution, cost_adjacent_solution; // Deklaracja zmiennych przechowujących koszty rozwiązań
	cost_current_solution = calcCost(current_solution); // Wyliczenie kosztu dla obecnego rozwiązania
	cost_best_solution = cost_current_solution; // Wyliczenie kosztu dla najlepszego rozwiązania
	//long int i = 0;
	//int prev_cost = cost_current_solution;
	while (worse_solution_counter < worse_acceptable) { // Dopóki licznik gorszych rozwiązań pod rząd jest mniejszy od akceptowalnej liczby tych rozwiązań
		adjacent_solution = adjacentSolution(current_solution);	// Znalezienie rozwiązania sąsiedniego
		cost_adjacent_solution = calcCost(adjacent_solution); // Wyliczenie kosztu dla znalezionego rozwiązania sąsiedniego

		if (cost_adjacent_solution < cost_best_solution) { // Jeśli znalezione rozwiązanie jest tańsze od najlepszego to wykonaj:
			best_solution = adjacent_solution; // Mianuj znalezione rozwiązanie na najlepsze
			cost_best_solution = cost_adjacent_solution; // Przypisz jego koszt jako najlepszy
		}

		if (cost_adjacent_solution < cost_current_solution) { // Jeśli znalezione rozwiązanie jest tańsze od obecnego to wykonaj:
			current_solution = adjacent_solution; // Mianuj znalezione rozwiązanie na obecne
			cost_current_solution = cost_adjacent_solution; // Przypisz jego koszt jako obecny
			worse_solution_counter = 0; // Wyzeruj licznik znalezionych gorszych rozwiązań pod rząd
		} else { // W przeciwnym razie
			++worse_solution_counter; // Inkrementuj licznik znalezionych gorszych rozwiązań pod rząd
			double delta = cost_adjacent_solution - cost_current_solution; // Oblicz różnicę kosztów (sąsiednie rozw. - obecne rozw.)
			double x = (rand() % 100000) / 100000.0; // Wylosuj liczbę z zakresu <0,1)
			if (x < (exp((-delta) / temperature))) { // Akceptujemy rozwiązanie z pewnym prawdopodobieństwem wyliczonym za pomocą e^(-delta / temperature).
				// Warunek wykona się z pewnym wyliczonym prawdopodobieństwem zależnym od różnicy kosztów ścieżki obecnie znalezionej i ścieżki obecnej, oraz od temperatury.
				// Prawdopobieństwo zwiększa się im mniejsza będzie różnica kosztów i zmniejsza się wraz z obniżaniem temperatury (temperatura obniża się stopniowo wraz z każdą iteracją).
				current_solution = adjacent_solution; // Mianuj znalezione rozwiązanie na obecne
				cost_current_solution = cost_adjacent_solution; // Przypisz jego koszt jako obecny
			}
		}
		temperature *= temperature_change_factor; // Zmniejszanie temperatury wg zadanego współczynnika
		/*++i;
		if (prev_cost != cost_current_solution)
		 file << "(" << i << "," << cost_current_solution << ")"
		 << std::endl;
		 prev_cost = cost_current_solution;*/
	}
	return best_solution;
}

// (Temperatura początkowa (int), współczynnik zmiany temperatury <0-1), współczynnik akceptacji gorszych rozwiązań (0,inf) )
void Annealing::enterParam(int beg_temp, double temp_change_factor,
		double worse_accept_factor) {
	this->begin_temperature = beg_temp;
	this->temperature_change_factor = temp_change_factor;
	this->worse_acceptable_factor = worse_accept_factor;
}

std::vector<int> Annealing::randomSolution(int number) {
	srand(time(NULL));
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

std::vector<int> Annealing::adjacentSolution(std::vector<int> res) {
	int x1 = rand() % (res.size() - 1);
	int x2 = rand() % (res.size() - 1);
	if (x1 == x2)
		x2 == res.size() - 2 ? --x2 : ++x2;
	std::swap(res[x1], res[x2]);
	res[res.size() - 1] = res[0];
	return res;
}
