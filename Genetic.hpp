/*
 * Genetic.hpp
 *
 *  Created on: 8 sty 2019
 *      Author: darek
 */

#ifndef GENETIC_HPP_
#define GENETIC_HPP_
#include "TSP.hpp"

struct PopValue {
	int index;
	int value;
};

class Genetic: public TSP {
	std::vector<std::vector<int>> population;
	std::vector<int> best_solution;
	int worse_solution_counter;

	int population_min_size;
	int population_max_size;
	float mutate_factor;
	int worse_acceptable_factor;

public:
/*
 * Macierz sąsiedztwa (vector<vector<int>>)
 * Początkowa wielkość populacji (int)
 * Maksymalna wielkość populacji (int)
 * Współczynnik mutacji (float <0;1>)
 * Mnożnik ilości akceptacji gorszych rozwiązań (float)
 */
	Genetic(std::vector<std::vector<int>> adjacency_matrix,
			int population_min_size, int population_max_size,
			float mutate_factor, float worse_acceptable_multiply_number);
	Genetic(int** adjacency_matrix, int matrix_size, int population_min_size,
			int population_max_size, float mutate_factor,
			float worse_acceptable_multiply_number);
	virtual ~Genetic();

	void start();
	std::vector<int> algorithm();

private:
	void generatePopulation();
	void sortPopulation();
	void checkBestSolution();
	bool endCondition();
	void reducePopulation();

	void crossPopulation();
	std::vector<int> cross(const std::vector<int>& first_population,
			const std::vector<int>& second_population);

	void mutatePopulation();
	void mutate(std::vector<int>& population);

	float getProbability();
	float randFloat(float min, float max);
	int randInt(int min, int max);

	void quickSort(PopValue* arr, int left, int right);
};

#endif /* GENETIC_HPP_ */
