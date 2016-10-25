/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright 2016, all rights reserved
*/

// File: Main.cpp
// Author: Douglas Kirkpatrick
// Description: Driver for TTT String Evolver Project 
// Date: 10/18/16
// Copyright 2016. All rights reserved 

#include <cmath>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

#include "PopulationController.h"
#include "BoardDictionary.h"

//Takes 2 strings as parameters, input configuration file and output file directory

//Config file (infile) should have the following variables in order, each on a separate line: 
//	size of population(integer)
//	size of Strategys(integer)
//	distribution of Strategys in the population(string, specific value)
//	number of generations(integer)
//	mutation method(string, specific value)
//	rate of mutations(double, 0 - 1)
//	selection method(string, specific value)
//	percent selected for reproduction(double, 0 - 1)
//	number of times the Strategy is evaluated(integer)

int main(int argc, char* argv[]){
/*	std::cout << argv[0] << std::endl;

	//String path to the config file
	std::string infilePath;

	//String path to the output file directory
	std::string outfilePath;

	//Reads in arguments if present
	if (argc > 1){
		infilePath = argv[1];
		outfilePath = argv[2];
	}
	else{
		//	Default values for testing
		infilePath = "E:\\StrategyEvolver\\TestIn.txt";
		outfilePath = "E:\\StrategyEvolver\\TestOut";
	}

	//Opens config file 
	std::ifstream infileStream(infilePath);

	//Variables for the simulation. See ConfigLayout.txt for explanation
	int sizePopulation = 100; 
	int sizeStrategy = 2;
	std::string distributionStrategy = "uniform";
	int numGenerations = 500; 
	std::string methodMutation = "Point";
	double rateMutation = 0.01; 
	std::string methodSelection = "elite"; 
	double rateSelection = 0.30; 
	int numEvals = 1; 


	if (infileStream.is_open()){
		//Reads all variables from the config file and sets them correctly
		infileStream >> sizePopulation >> sizeStrategy >> distributionStrategy; 
		infileStream >> numGenerations >> methodMutation >> rateMutation; 
		infileStream >> methodSelection >> rateSelection >> numEvals; 
		infileStream.close(); 
	}

	PopulationController m_controller(sizePopulation, sizeStrategy, distributionStrategy, numGenerations,
		methodMutation, rateMutation, methodSelection, rateSelection, numEvals); 
	m_controller.run(); 
	std::cout << "done run" << std::endl; 
	m_controller.outputData(outfilePath);

	std::cout << "Done" << std::endl; 
	*/

	auto p = AccessDictionary::getBoardDictionary().dict(); 
	int count; 
	int max = 0; 
	for (auto member : p) {
		count++; 
		if (member.second.first > max) {
			max = member.second.first; 
		}
	}

	std::cout << "Count: " << count << "\nMax: " << max;


	int temp;
	std::cout << "Done" << std::endl;
	std::cin >> temp; 

	return 0;
}
