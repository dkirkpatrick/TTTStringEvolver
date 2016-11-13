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
#include "BoardDictionary.h"
#include "TTTEngine.h"
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
	int outputInterval;
	bool startAdvantage; 
	int gamesVsRandom;

	//Reads in arguments if present
	if (argc > 1){
		if (argc < 10){
			std::cout << "The expected inputs are: "<< std::endl;
			std::cout << "\trandomSeed outfilePath winVal drawVal numGenerations " << std::endl;
			std::cout << "\tsizePopulation outputInterval startAdvantage gamesVsRandom" << std::endl;
			std::cout << "in that order" << std::endl;
			std::cout << "Exiting." << std::endl;
			return 0; 
		} else {
			randomSeed = atoi(argv[1]);
			outfilePath = argv[2];
			winval = atof(argv[3]);
			drawval = atof(argv[4]);
			numGenerations = atoi(argv[5]);
			sizePopulation = atoi(argv[6]);
			outputInterval = atoi(argv[7]);
			if (tolower(argv[8][0]) == 't') {
				startAdvantage = true;
			}
			else {
				startAdvantage = false;
			}
			gamesVsRandom = atoi(argv[9]);
		}
	}
	else{
		randomSeed = 100; 
		outfilePath = "./";
		winval = 1.0; 
		drawval = 1.0; 
		numGenerations = 100;
		sizePopulation = 200;
		outputInterval = 100; 
		startAdvantage = false; 
		gamesVsRandom = 200; 
	}

	Random::getCommonGenerator().seed(randomSeed); 
	
	int sizeStrategy = 3164;
	std::string distributionStrategy = "validRand";
	std::string methodMutation = "validPoint";
	//double rateMutation = 0.001;
	double rateMutation = 0.001;
	std::string methodSelection = "roulette"; 
	double rateSelection = 0.40; 
	int numEvals = 1; 

	PopulationController m_controller(sizePopulation, sizeStrategy, distributionStrategy, numGenerations, outputInterval, outfilePath,
		methodMutation, rateMutation, methodSelection, rateSelection, numEvals, winval, drawval, randomSeed, startAdvantage, gamesVsRandom);
	m_controller.runLODOnly(); 

	std::cout << "Done" << std::endl; 
		
	return 0;
}
