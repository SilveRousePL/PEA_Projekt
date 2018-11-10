/*
 * App.cpp
 *
 *  Created on: 29 paź 2018
 *      Author: darek
 */

#include "App.hpp"

App::App() : graph() {
	try {
		graph.loadFromFile("tsp.txt");
		std::cout << graph << std::endl;
	} catch(Exception & e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "OK!" << std::endl;
	// TODO Auto-generated constructor stub
}

App::~App() {
	// TODO Auto-generated destructor stub
}

