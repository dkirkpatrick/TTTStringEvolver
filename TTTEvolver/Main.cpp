/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
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
#include "Random.h"

// Takes seed, output file path, win reward, and draw reward 
// as input in that order with types:
// int, string, double, double 

int main(int argc, char* argv[]){

	std::cout << argv[0] << std::endl;

	//String path to the output file directory
	std::string outfilePath;

	//Random seed for experiment
	int randomSeed; 

	double winval; 
	double drawval; 
	int numGenerations;
	int sizePopulation;
	
	//Reads in arguments if present
	if (argc > 1){
		randomSeed = atoi(argv[1]); 
		outfilePath = argv[2];
		winval = atof(argv[3]); 
		drawval = atof(argv[4]); 
		numGenerations = atoi(argv[5]); 
		sizePopulation = atoi(argv[6]); 
	}
	else{
		randomSeed = 100; 
		outfilePath = "./";
		winval = 1.0; 
		drawval = 0.5; 
		numGenerations = 10;
		sizePopulation = 200;
	}

	Random::getCommonGenerator().seed(randomSeed); 
	
	int sizeStrategy = 3164;
	std::string distributionStrategy = "random";
	std::string methodMutation = "point";
	double rateMutation = 0.001; 
	std::string methodSelection = "roulette"; 
	double rateSelection = 0.40; 
	int numEvals = 1; 

	PopulationController m_controller(sizePopulation, sizeStrategy, distributionStrategy, numGenerations,
		methodMutation, rateMutation, methodSelection, rateSelection, numEvals, winval, drawval, randomSeed); 
	m_controller.run(); 
	std::cout << "Done run" << std::endl; 
	m_controller.outputData(outfilePath);

	std::cout << "Done" << std::endl; 
		

	return 0;
}
