cmake_minimum_required(VERSION 3.13)
project(PEA_Projekt)

set(CMAKE_CXX_STANDARD 14)

add_executable(PEA_Projekt main.cpp Annealing.hpp Annealing.cpp App.hpp App.cpp BranchAndBound.hpp BranchAndBound.cpp BruteForce.hpp BruteForce.cpp Exception.hpp Genetic.hpp Genetic.cpp Graph.hpp Graph.cpp Test.hpp Test.cpp Timer.hpp TSP.hpp TSP.cpp)