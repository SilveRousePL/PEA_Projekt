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
	while (enterFileName())
		;
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
				<< "2. Branch and Bound" << std::endl << "8. Pokaż graf"
				<< std::endl << "9. Wczytaj plik ponownie" << std::endl
				<< "0. Wyjście" << std::endl;
		std::cin >> option;
		std::cout << std::endl;
		switch (option) {
		case 1:
			std::cout << "METODA BRUTE FORCE" << std::endl;
			timer.startTimer();
			graph.solveTSP_BF();
			timer.stopTimer();
			std::cout << "Czas: " << timer.getTimeMs() << " ms" << std::endl
					<< std::endl;
			break;
		case 2:
			std::cout << "METODA BRANCH AND BOUND" << std::endl;
			timer.startTimer();
			graph.solveTSP_BB();
			timer.stopTimer();
			std::cout << "Czas: " << timer.getTimeUs() << "us ("
					<< timer.getTimeMs() << " ms)" << std::endl;
			break;
		case 8:
			showGraph();
			break;
		case 9:
			while (enterFileName())
				;
			break;
		case 0:
			return;
		default:
			std::cout << "Błędna opcja" << std::endl;
		}
	}
}

bool App::enterFileName() {
	try {
		std::string name;
		std::cout << "Wprowadź nazwę pliku: ";
		std::cin >> name;
		graph.loadFromFile(name);
		std::cout << "Graf wczytano" << std::endl;
	} catch (Exception & e) {
		std::cout << "BŁĄD: " << e.what() << std::endl;
		return true;
	}
	return false;
}

void App::showGraph() {
	std::cout << "Ilość wierzchołków: " << graph.getVertexNumber() << std::endl;
	graph.print();
}
