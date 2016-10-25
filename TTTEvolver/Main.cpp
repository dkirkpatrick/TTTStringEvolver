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
//	size of portfolios(integer)
//	distribution of portfolios in the population(string, specific value)
//	number of generations(integer)
//	mutation method(string, specific value)
//	rate of mutations(double, 0 - 1)
//	selection method(string, specific value)
//	percent selected for reproduction(double, 0 - 1)
//	number of times the portfolio is evaluated(integer)

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
		infilePath = "E:\\PortfolioEvolver\\TestIn.txt";
		outfilePath = "E:\\PortfolioEvolver\\TestOut";
	}

	//Opens config file 
	std::ifstream infileStream(infilePath);

	//Variables for the simulation. See ConfigLayout.txt for explanation
	int sizePopulation = 100; 
	int sizePortfolio = 2;
	std::string distributionPortfolio = "uniform";
	int numGenerations = 500; 
	std::string methodMutation = "randomAdd";
	double rateMutation = 0.01; 
	std::string methodSelection = "elite"; 
	double rateSelection = 0.30; 
	int numEvals = 1; 


	if (infileStream.is_open()){
		//Reads all variables from the config file and sets them correctly
		infileStream >> sizePopulation >> sizePortfolio >> distributionPortfolio; 
		infileStream >> numGenerations >> methodMutation >> rateMutation; 
		infileStream >> methodSelection >> rateSelection >> numEvals; 
		infileStream.close(); 
	}

	PopulationController m_controller(sizePopulation, sizePortfolio, distributionPortfolio, numGenerations,
		methodMutation, rateMutation, methodSelection, rateSelection, numEvals); 
	m_controller.run(); 
	std::cout << "done run" << std::endl; 
	m_controller.outputData(outfilePath);

	std::cout << "Done" << std::endl; 
	*/

	auto p = AccessDictionary::getBoardDictionary().dict(); 

	return 0;
}
