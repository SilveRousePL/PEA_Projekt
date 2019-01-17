/*
 * Genetic.cpp
 *
 *  Created on: 8 sty 2019
 *      Author: darek
 */

#include "Genetic.hpp"

/*
 * Macierz sąsiedztwa (vector<vector<int>>)
 * Początkowa wielkość populacji (int)
 * Maksymalna wielkość populacji (int)
 * Współczynnik mutacji (float <0;1>)
 * Mnożnik ilości akceptacji gorszych rozwiązań (float)
 */
Genetic::Genetic(std::vector<std::vector<int>> adjacency_matrix,
                 int population_min_size, int population_max_size, float mutate_factor,
                 float worse_acceptable_multiply_number) :
        TSP(adjacency_matrix), population_min_size(population_min_size), population_max_size(
        population_max_size), mutate_factor(mutate_factor), worse_acceptable_factor(
        worse_acceptable_multiply_number * vertex_number) {
    worse_solution_counter = 0;
}

Genetic::Genetic(int **adjacency_matrix, int matrix_size,
                 int population_min_size, int population_max_size, float mutate_factor,
                 float worse_acceptable_multiply_number) :
        TSP(adjacency_matrix, matrix_size), population_min_size(
        population_min_size), population_max_size(population_max_size), mutate_factor(
        mutate_factor), worse_acceptable_factor(
        worse_acceptable_multiply_number * vertex_number) {
    worse_solution_counter = 0;
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
        reducePopulation();
        crossPopulation();
        mutatePopulation();
        sortPopulation();
        checkBestSolution();
    }
    best_solution.push_back(best_solution[0]);
    return best_solution;
}

void Genetic::generatePopulation() {
    population.reserve(population_max_size);

    for (int i = 0; i < population_min_size; ++i) {
        int *tab_i = new int[vertex_number];
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
    PopValue *arr = new PopValue[population.size()];
    for (uint i = 0; i < population.size(); ++i) {
        arr[i].index = i;
        arr[i].value = calcCostWithBeginAndEnd(population[i]);
    }

    quickSort(arr, 0, population.size() - 1);

    std::vector<std::vector<int>> new_population;
    new_population.reserve(population.size());
    for (uint i = 0; i < population.size(); ++i) {
        new_population.push_back(population[arr[i].index]);
    }

    population = new_population;
    delete[] arr;
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
    population.resize(population_min_size);
    population.reserve(population_max_size);
}

void Genetic::crossPopulation() {
    for (int i = 0; i < population_max_size - population_min_size; ++i) {
        std::vector<int> population_a = population[randInt(0,
                                                           population_min_size - 1)];
        std::vector<int> population_b = population[randInt(0,
                                                           population_min_size - 1)];
        population.push_back(cross(population_a, population_b));
    }
}

std::vector<int> Genetic::cross(const std::vector<int>& first_population,
                                const std::vector<int>& second_population) {
    std::vector<int> child;
    child.reserve(vertex_number);

    int begin_index = randInt(0, vertex_number / 2);
    for (int i = 0; i < vertex_number / 2; ++i) {
        child.push_back(first_population[begin_index + i]);
    }

    for (int i = 0; i < vertex_number; ++i) {
        bool is_exist = false;
        for (int j = 0; j < child.size(); ++j) {
            if (second_population[i] == child[j]) {
                is_exist = true;
                break;
            }
        }
        if (!is_exist) {
            child.push_back(second_population[i]);
        }
    }

    /*std::cout << "A: ";
    for (int i = 0; i < first_population.size(); ++i) {
        std::cout << first_population[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "B: ";
    for (int i = 0; i < second_population.size(); ++i) {
        std::cout << second_population[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "C: ";
    for (int i = 0; i < child.size(); ++i) {
        std::cout << child[i] << " ";
    }
    std::cout << std::endl << "--------------------------" << std::endl;*/

    return child;
}

void Genetic::mutatePopulation() {
    for (int i = 0; i < population.size(); ++i) {
        if (getProbability() < mutate_factor) {
            mutate(population[i]);
        }
    }
}

//Inwersja
void Genetic::mutate(std::vector<int> &population) {
    int begin = randInt(0, vertex_number);
    int end = randInt(begin, vertex_number);
    std::reverse(population.begin() + begin, population.begin() + end);
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

void Genetic::quickSort(PopValue *arr, int left, int right) {
    int i = left, j = right;
    PopValue tmp;
    PopValue pivot = arr[(left + right) / 2];
    while (i <= j) {
        while (arr[i].value < pivot.value)
            ++i;
        while (arr[j].value > pivot.value)
            --j;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            ++i;
            --j;
        }
    };
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}
