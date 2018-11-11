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
	std::string name;
	std::cin >> name;
	graph.loadFromFile(name);
	std::cout << graph << std::endl;

	timer.startTimer();
	graph.solveTSP();
	timer.stopTimer();
	std::cout << "Czas: " << timer.getTimeMs() << " ms" << std::endl;

}

App::~App() {
	// TODO Auto-generated destructor stub
}

