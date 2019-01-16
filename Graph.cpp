/*
 * Graph.cpp
 *
 *  Created on: 6 lis 2018
 *      Author: darek
 */

#include "Graph.hpp"

Graph::Graph(int matrix_size) :
        vertex_number(0), edge_number(0) {
    if (vertex_number > 0)
        adjacency_matrix.reserve(matrix_size);
}

Graph::~Graph() {
    // TODO Auto-generated destructor stub
}

void Graph::addVertex() {
    std::vector<int> vec;
    for (int i = 0; i < vertex_number + 1; i++) {
        vec.push_back(-1);
    }
    for (int i = 0; i < vertex_number; i++) {
        adjacency_matrix[i].push_back(-1);
    }
    adjacency_matrix.push_back(vec);
    vertex_number++;
}

void Graph::setEdge(int begin, int end, int value) {
    if (begin > vertex_number || begin < 0) {
        throw RangeExceeded("Begin vertex is out of range!");
    }
    if (end > vertex_number || end < 0) {
        throw RangeExceeded("End vertex is out of range!");
    }
    if (begin == end) {
        throw RangeExceeded("Begin and end vertex is the same!");
    }
    if (value < -1) {
        throw RangeExceeded("Value is out of range!");
    }
    if (adjacency_matrix[begin][end] != value) {
        if (value == -1)
            edge_number--;
        else
            edge_number++;
    }
    adjacency_matrix[begin][end] = value;
}

void Graph::removeVertex(int vertex) {
    if (vertex > vertex_number || vertex < 0) {
        throw RangeExceeded("Vertex is out of range!");
    }
    for (int i = 0; i < vertex_number; i++) {
        adjacency_matrix[i].erase(adjacency_matrix[i].begin() + vertex);
    }
    adjacency_matrix.erase(adjacency_matrix.begin() + vertex);
    vertex_number--;
}

void Graph::removeEdge(int begin, int end) {
    setEdge(begin, end, -1);
}

int Graph::getVertexNumber() {
    return vertex_number;
}

int Graph::getEdgesNumber() {
    return edge_number;
}

std::string Graph::getFilename() {
    return filename;
}

void Graph::loadFromFile(std::string filename) {
    std::fstream handle;
    handle.open(filename, std::ios::in);
    if (!handle.is_open())
        throw FileException("File isn't open!");

    Matrix result_adjacency_matrix;

    std::string check;
    handle >> check;
    for (size_t i = 0; i < check.length(); i++) {
        if (check[i] >= '0' && check[i] <= '9') {
            if (i == check.length() - 1)
                handle.seekg(0, std::ios_base::beg);
            continue;
        } else {
            break;
        }
    }

    int result_vertex_number = 0;
    handle >> result_vertex_number;

    for (int i = 0; i < result_vertex_number; i++) {
        std::vector<int> vec;
        vec.reserve(result_vertex_number);
        int tmp_value = -1;
        for (int j = 0; j < result_vertex_number; j++) {
            handle >> tmp_value;
            vec.push_back(tmp_value);
        }
        result_adjacency_matrix.push_back(vec);
    }
//TODO: Checking integrity
    /*if (!checkIntegrity(result_adjacency_matrix))
     throw FileException("File isn't valid!");*/

    vertex_number = result_vertex_number;
    adjacency_matrix = result_adjacency_matrix;
    this->filename = filename;
}

void Graph::saveToFile(std::string filename) {
    std::fstream handle;
    handle.open("." + filename + ".tmp", std::ios::out | std::ios::trunc);
    if (!handle.is_open())
        throw FileException("File isn't open!");
    handle << getVertexNumber() << std::endl;
    handle << *this << std::endl;
}

void Graph::solveTSP(TSP_algorithm alg) {
    TSP *tsp = nullptr;
    Annealing *tsp_annealing = nullptr;
    switch (alg) {
        case TSP_algorithm::BRUTEFORCE:
            tsp = new BruteForce(adjacency_matrix);
            break;
        case TSP_algorithm::BRANCH_AND_BOUND:
            tsp = new BranchAndBound(adjacency_matrix);
            break;
        case TSP_algorithm::SIMULATED_ANNEALING:
            tsp = new Annealing(adjacency_matrix);
            tsp_annealing = dynamic_cast<Annealing *>(tsp);
            int beg_temp;
            double temp_change_factor, worse_accept_factor;
            std::cout << "Podaj parametry wyszukiwania" << std::endl
                      << "(Temperatura początkowa (int), współczynnik zmiany temperatury <0-1), współczynnik akceptacji gorszych rozwiązań (0,inf) ): "
                      << std::endl;
            //
            std::cin >> beg_temp >> temp_change_factor >> worse_accept_factor;
            tsp_annealing->enterParam(beg_temp, temp_change_factor,
                                      worse_accept_factor);
            //tsp_annealing->enterParam(500, 0.99, 50);
            break;
        case TSP_algorithm::GENETIC:
/*
 * Macierz sąsiedztwa (vector<vector<int>>)
 * Początkowa wielkość populacji (int)
 * Maksymalna wielkość populacji (int)
 * Współczynnik mutacji (float <0;1>)
 * Mnożnik ilości akceptacji gorszych rozwiązań (float)
 */
            int min_population, max_population;
            double mutate_factor, worse_accept_factor_g;
            std::cout << "Podaj parametry wyszukiwania" << std::endl
                      << "(Początkowa wielkość populacji (int), Maksymalna wielkość populacji (int), Współczynnik mutacji (float <0;1>), Mnożnik ilości akceptacji gorszych rozwiązań (float)): "
                      << std::endl;
            std::cin >> min_population >> max_population >> mutate_factor >> worse_accept_factor_g;
            tsp = new Genetic(adjacency_matrix, min_population, max_population, mutate_factor, worse_accept_factor_g);
            //tsp = new Genetic(adjacency_matrix, 10, 20, 0.1, 0.5);
            break;
        default:
            throw NotImplemented("Algorithm is not implemented");
    }
    std::cout << "START!" << std::endl;
    startTimer();
    tsp->start();
    stopTimer();
    Path algorithm_result_path = tsp->getResultPath();
    int algorithm_result_cost = tsp->getResultCost();
    for (size_t i = 0; i < algorithm_result_path.size() - 1; i++)
        std::cout << algorithm_result_path[i] << "->";
    std::cout << algorithm_result_path[algorithm_result_path.size() - 1]
              << std::endl;
    std::cout << "Koszt = " << algorithm_result_cost << std::endl;
    std::cout << "Czas: " << getTimeUs() << "us (" << getTimeMs() << " ms)"
              << std::endl;

    if (tsp != nullptr)
        delete tsp;
}

void Graph::annealingTest() {
    system("ls AnnealingTest -w 1 -v > annealingTestFN.txt");
    std::fstream handle;
    handle.open("annealingTestFN.txt", std::ios::in);
    std::vector<std::string> input;
    while (!handle.eof()) {
        std::string tmp;
        getline(handle, tmp);
        input.push_back(tmp);
    }
    input.pop_back();
    handle.close();

    int beg_temp, measure_number;
    double temp_change_factor, worse_accept_factor;
    std::cout << "Podaj parametry wyszukiwania" << std::endl
              << "(Temperatura początkowa (int), współczynnik zmiany temperatury <0-1), współczynnik akceptacji gorszych rozwiązań (0,inf) , ilość pomiarów (int)): "
              << std::endl;
    std::cin >> beg_temp >> temp_change_factor >> worse_accept_factor
             >> measure_number;

    handle.open("annealingTestRes.txt", std::ios::out | std::ios::trunc);
    handle << "Nazwa" << "\t" << "Ilość wierzchołków" << "\t" << "Średni czas"
           << "\t" << "Najlepszy koszt" << std::endl;
    std::cout << "Nazwa" << "\t" << "Średni czas" << "\t" << "Najlepszy koszt"
              << std::endl;
    for (int file_i = 0; file_i < input.size(); file_i++) {
        std::cout << input[file_i] << "\t";
        loadFromFile("AnnealingTest/" + input[file_i]);
        Annealing tsp(adjacency_matrix);
        long int res_time = 0;
        int best_cost = INT_MAX;
        tsp.enterParam(beg_temp, temp_change_factor, worse_accept_factor);
        for (int res_i = 0; res_i < measure_number; res_i++) {
            startTimer();
            tsp.start();
            stopTimer();
            res_time += getTimeMs();
            if (tsp.getResultCost() < best_cost)
                best_cost = tsp.getResultCost();
        }
        std::cout << res_time / measure_number << "\t" << best_cost
                  << std::endl;
        handle << input[file_i] << "\t" << vertex_number << "\t"
               << res_time / measure_number << "\t" << best_cost << std::endl;
    }
    handle.close();
    // Temperatura początkowa (int)
    // współczynnik zmiany temperatury <0-1)
    // współczynnik akceptacji gorszych rozwiązań (0,inf)
}

void Graph::geneticTest() {
    system("ls GeneticTest -w 1 -v > geneticTestFN.txt");
    std::fstream handle;
    handle.open("geneticTestFN.txt", std::ios::in);
    std::vector<std::string> input;
    while (!handle.eof()) {
        std::string tmp;
        getline(handle, tmp);
        input.push_back(tmp);
    }
    input.pop_back();
    handle.close();

    int min_population, max_population, measure_number;
    double mutate_factor, worse_accept_factor;
    std::cout << "Podaj parametry wyszukiwania" << std::endl
              << "(Początkowa wielkość populacji (int), Maksymalna wielkość populacji (int), Współczynnik mutacji (float <0;1>), Mnożnik ilości akceptacji gorszych rozwiązań (float) , ilość pomiarów (int)): "
              << std::endl;
    std::cin >> min_population >> max_population >> mutate_factor >> worse_accept_factor
             >> measure_number;

    handle.open("geneticTestRes.txt", std::ios::out | std::ios::trunc);
    handle << "Nazwa" << "\t" << "Ilość wierzchołków" << "\t" << "Średni czas"
           << "\t" << "Najlepszy koszt" << std::endl;
    std::cout << "Nazwa" << "\t" << "Średni czas" << "\t" << "Najlepszy koszt"
              << std::endl;
    for (int file_i = 0; file_i < input.size(); file_i++) {
        std::cout << input[file_i] << "\t";
        loadFromFile("GeneticTest/" + input[file_i]);
        Genetic tsp(adjacency_matrix, min_population, max_population, mutate_factor, worse_accept_factor);
        long int res_time = 0;
        int best_cost = INT_MAX;
        for (int res_i = 0; res_i < measure_number; res_i++) {
            startTimer();
            tsp.start();
            stopTimer();
            res_time += getTimeMs();
            if (tsp.getResultCost() < best_cost)
                best_cost = tsp.getResultCost();
        }
        std::cout << res_time / measure_number << "\t" << best_cost
                  << std::endl;
        handle << input[file_i] << "\t" << vertex_number << "\t"
               << res_time / measure_number << "\t" << best_cost << std::endl;
    }
    handle.close();
    /*
 * Macierz sąsiedztwa (vector<vector<int>>)
 * Początkowa wielkość populacji (int)
 * Maksymalna wielkość populacji (int)
 * Współczynnik mutacji (float <0;1>)
 * Mnożnik ilości akceptacji gorszych rozwiązań (float)
 */
}

void Graph::print() {
    std::cout << "     ";
    for (int i = 0; i < getVertexNumber(); i++) {
        std::cout << std::setw(3) << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < getVertexNumber() * 5 + 8; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
    for (int i = 0; i < getVertexNumber(); i++) {
        std::cout << std::setw(3) << i << " |";
        for (int j = 0; j < getVertexNumber(); j++) {
            std::cout << std::setw(3) << adjacency_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::vector<int> &Graph::operator[](uint index) {
    return adjacency_matrix[index];
}

std::ostream &operator<<(std::ostream &ostr, Graph &obj) {
    for (int i = 0; i < obj.getVertexNumber(); i++) {
        for (int j = 0; j < obj.getVertexNumber(); j++) {
            ostr << std::setw(3) << obj[i][j] << " ";
        }
        ostr << std::endl;
    }
    return ostr;
}

bool Graph::checkIntegrity(Matrix adjacency_matrix) {
//TODO: sprawdzenie zgodności macierzy
    return true;
}
