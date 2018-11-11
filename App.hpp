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
#include "Timer.hpp"

class App {
	Graph graph;
	Timer timer;

public:
	App();
	virtual ~App();
};

#endif /* APP_HPP_ */
