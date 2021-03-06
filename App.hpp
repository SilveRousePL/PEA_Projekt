/*
 * App.hpp
 *
 *  Created on: 29 paź 2018
 *      Author: darek
 */

#ifndef APP_HPP_
#define APP_HPP_
#include <iostream>
#include "Graph.hpp"

class App {
	Graph graph;

public:
	App();
	App(std::string filename);
	virtual ~App();
	void run();
	bool enterFileName(std::string filename = "");
	void showGraph();
};

#endif /* APP_HPP_ */
