/*
 * App.cpp
 *
 *  Created on: 29 paź 2018
 *      Author: darek
 */

#include "App.hpp"
#include <vector>

App::App() :
        graph() {
    while (enterFileName());
}

App::App(std::string filename) :
        graph() {
    enterFileName(filename);
}

App::~App() {
    // TODO Auto-generated destructor stub
}

void App::run() {
    while (true) {
        int option = -1;
        std::cout << "--------------------------------------" << std::endl
                  << "Plik: " << graph.getFilename() << std::endl
                  << "Wierzchołków: " << graph.getVertexNumber() << std::endl
                  << "Menu:" << std::endl << "1. Brute Force" << std::endl
                  << "2. Branch and Bound" << std::endl
                  << "3. Simulated Annealing" << std::endl
                  << "4. Genetic Algorithm" << std::endl
                  << "6. Autotest Simulated Annealing" << std::endl
                  << "7. Autotest Genetic" << std::endl
                  << "8. Pokaż graf" << std::endl << "9. Wczytaj plik ponownie"
                  << std::endl << "0. Wyjście" << std::endl;
        std::cin >> option;
        std::cout << std::endl;
        try {
            switch (option) {
                case 1:
                    std::cout << "METODA BRUTE FORCE" << std::endl;
                    graph.solveTSP(BRUTEFORCE);
                    break;
                case 2:
                    std::cout << "METODA BRANCH AND BOUND" << std::endl;
                    graph.solveTSP(BRANCH_AND_BOUND);
                    break;
                case 3:
                    std::cout << "METODA SIMULATED ANNEALING" << std::endl;
                    graph.solveTSP(SIMULATED_ANNEALING);
                    break;
                case 4:
                    std::cout << "METODA GENETIC" << std::endl;
                    graph.solveTSP(GENETIC);
                    break;
                case 6:
                    std::cout << "METODA SIMULATED ANNEALING - AUTOTEST"
                              << std::endl;
                    graph.annealingTest();
                    break;
                case 7:
                    std::cout << "METODA GENETIC - AUTOTEST"
                              << std::endl;
                    graph.geneticTest();
                    break;
                case 8:
                    showGraph();
                    break;
                case 9:
                    while (enterFileName());
                    break;
                case 0:
                    return;
                default:
                    std::cout << "Błędna opcja" << std::endl;
            }
        } catch (NotImplemented &e) {
            std::cout << e.what() << std::endl;
        }
    }
}

bool App::enterFileName(std::string filename) {
    try {
        std::string name;
        if (filename == "") {
            std::cout << "Wprowadź nazwę pliku: ";
            std::cin >> name;
        } else {
            name = filename;
        }
        graph.loadFromFile(name);
        std::cout << "Graf wczytano" << std::endl;
    } catch (Exception &e) {
        std::cout << "BŁĄD: " << e.what() << std::endl;
        return true;
    }
    return false;
}

void App::showGraph() {
    std::cout << "Ilość wierzchołków: " << graph.getVertexNumber() << std::endl;
    graph.print();
}
