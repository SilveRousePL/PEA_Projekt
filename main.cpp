/*
 * main.cpp
 *
 *  Created on: 29 paź 2018
 *      Author: darek
 */

#include "App.hpp"

int main(int argc, char* argv[]) {
	srand(time(NULL));
	std::vector<std::string> options;
	for (int i = 0; i < argc; i++) {
		std::string temp = std::string(argv[i]);
		options.push_back(temp);
	}
	std::string filename = "";
	for (int i = 0; i < options.size(); ++i) {
		if (options[i] == "-file") {
			filename = options[i + 1];
		}
	}

	App* app;
	if (filename != "") {
		app = new App(filename);
	} else {
		app = new App();
	}
	app->run();
	return 0;
}
