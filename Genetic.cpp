/*
 * Genetic.cpp
 *
 *  Created on: 8 sty 2019
 *      Author: darek
 */

#include "Genetic.hpp"

/*
 * Macierz sąsiedztwa (vector<vector<int>>)
 * Wielkość populacji (int)
 * Współczynnik krzyżowania (float <0;1>)
 * Współczynnik mutacji (float <0;1>)
 * Mnożnik ilości akceptacji gorszych rozwiązań
 */
Genetic::Genetic(std::vector<std::vector<int>> adjacency_matrix,
		int population_size, float cross_factor, float mutate_factor,
		int worse_acceptable_multiply_number) :
		TSP(adjacency_matrix), population_size(population_size), cross_factor(
				cross_factor), mutate_factor(mutate_factor), worse_acceptable_factor(
				worse_acceptable_multiply_number * vertex_number) {
	worse_solution_counter = 0;
	population.reserve(population_size);
}

Genetic::Genetic(int** adjacency_matrix, int matrix_size, int population_size,
		float cross_factor, float mutate_factor,
		int worse_acceptable_multiply_number) :
		TSP(adjacency_matrix, matrix_size), population_size(population_size), cross_factor(
				cross_factor), mutate_factor(mutate_factor), worse_acceptable_factor(
				worse_acceptable_multiply_number * vertex_number) {
	worse_solution_counter = 0;
	population.reserve(population_size);
}

Genetic::~Genetic() {

}

void Genetic::start() {
	this->result_path = this->algorithm();
	this->result_cost = calcCost(this->result_path);
}

std::vector<int> Genetic::algorithm() {
	generatePopulation();
	sortPopulation();
	while (endCondition()) {
		std::cout << "Reduce" << std::endl;
		reducePopulation();
		std::cout << "Cross" << std::endl;
		crossPopulation();
		std::cout << "Mutate" << std::endl;
		mutatePopulation();
		std::cout << "Sort" << std::endl;
		sortPopulation();
		std::cout << "Check" << std::endl;
		checkBestSolution();
	}
	std::cout << "End" << std::endl;
	best_solution.push_back(best_solution[0]);
	return best_solution;
}

void Genetic::generatePopulation() {
	for (int i = 0; i < population_size; ++i) {
		int* tab_i = new int[vertex_number];
		for (int i = 0; i < vertex_number; ++i)
			tab_i[i] = i;

		std::vector<int> res;
		for (int i = 0; i < vertex_number; ++i) {
			int x = rand() % vertex_number;
			if (tab_i[x] == -1) {
				--i;
				continue;
			}
			res.push_back(tab_i[x]);
			tab_i[x] = -1;
		}
		delete[] tab_i;
		population.push_back(res);
	}
	best_solution = population[0];
}

void Genetic::sortPopulation() {
	std::sort(population.begin(), population.end(),
			[this] (const std::vector<int>& v1, const std::vector<int>& v2) -> bool
			{
				return this->calcCostWithBeginAndEnd(v1) < this->calcCostWithBeginAndEnd(v2);
			});
	/*
	 for (int i = 0; i < population_size; ++i) {
	 std::cout << calcCostWithBeginAndEnd(population[i]) << std::endl;
	 }*/
}

void Genetic::checkBestSolution() {
	if (calcCostWithBeginAndEnd(population[0])
			< calcCostWithBeginAndEnd(best_solution)) {
		best_solution = population[0];
		worse_solution_counter = 0;
	} else {
		++worse_solution_counter;
	}
}

bool Genetic::endCondition() {
	if (worse_solution_counter < worse_acceptable_factor)
		return true;
	return false;
}

void Genetic::reducePopulation() {
	std::vector<std::vector<int>> reduced_population;
	for (int i = 0; i < population_size; ++i) {
		reduced_population.push_back(population[i]);
	}
	population = reduced_population;
}

//Ograniczyć jakoś generowanie populacji
void Genetic::crossPopulation() {
	population.reserve(population_size * population_size + population_size);
	for (int i = 0; i < population_size; ++i) {
		for (int j = 0; j < population_size; ++j) {
			if (getProbability() < cross_factor) {
				population.push_back(cross(population[i], population[j]));
			}
		}
	}
}

//PMX - TODO: sprawdzić czy dobrze
/*std::vector<int> Genetic::cross(const std::vector<int>& first_population,
 const std::vector<int>& second_population) {
 std::vector<int> child = std::vector<int>(vertex_number, -1);

 int begin = randInt(0, vertex_number);
 int end = randInt(begin, vertex_number);

 for (int i = begin; i < end; ++i) {
 child[i] = first_population[i];
 }
 for (int i = begin; i < end; ++i) {
 if (!isAlreadyThere(child, second_population[i])) {
 int index = indexOfValue(second_population, first_population[i]);
 while (index > begin && index < end) {
 index = indexOfValue(second_population,
 first_population[index]);
 }
 child[index] = second_population[i];
 }
 }
 for (int i = 0; i < vertex_number; ++i) {
 if (child[i] == -1)
 child[i] = second_population[i];
 }
 return child;
 }*/

std::vector<int> Genetic::cross(const std::vector<int>& first_population,
		const std::vector<int>& second_population) {
	std::vector<int> child = std::vector<int>(vertex_number, -1);
	int* child = new int[vertex_number];

	int begin = randInt(0, vertex_number);
	int end = randInt(begin, vertex_number);

	for (int i = begin; i < end; ++i) {
		child[i] = first_population[i];
	}
	for (int i = begin; i < end; ++i) {
		if (!isAlreadyThere(child, second_population[i])) {
			int index = indexOfValue(second_population, first_population[i]);
			while (index > begin && index < end) {
				index = indexOfValue(second_population,
						first_population[index]);
			}
			child[index] = second_population[i];
		}
	}
	for (int i = 0; i < vertex_number; ++i) {
		if (child[i] == -1)
			child[i] = second_population[i];
	}
	return child;
}

void Genetic::mutatePopulation() {
	for (int i = 0; i < population_size; ++i) {
		if (getProbability() < mutate_factor) {
			mutate(population[i]);
		}
	}
}

//Inwersja
void Genetic::mutate(std::vector<int>& population) {
	int begin = randInt(0, vertex_number);
	int end = randInt(begin, vertex_number);
	std::reverse(population.begin() + begin, population.begin() + end);
}

bool Genetic::isAlreadyThere(const std::vector<int>& v, int value) {
	for (int x : v) {
		if (x == value)
			return true;
	}
	return false;
}

int Genetic::indexOfValue(const std::vector<int>& v, int value) {
	for (uint i = 0; i < v.size(); ++i) {
		if (v[i] == value)
			return i;
	}
	return -1;
}

float Genetic::getProbability() {
	return randFloat(0.0, 1.0);
}

float Genetic::randFloat(float min, float max) {
	float random = ((float) rand()) / (float) RAND_MAX;
	float range = max - min;
	return (random * range) + min;
}

int Genetic::randInt(int min, int max) {
	return (rand() % (max - min + 1) + min);
}
