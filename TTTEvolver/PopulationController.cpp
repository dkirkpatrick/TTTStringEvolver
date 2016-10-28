/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#include "PopulationController.h"
#include "RouletteSelection.h"
#include "PointMutator.h"
#include "EliteSelection.h"
#include <iostream>
#include <fstream>
#include "Random.h"
#include "TTTPlayers.h"

PopulationController::PopulationController(int sizePop, int sizePort, std::string distPort, int numGen, std::string metMuta,
	double rateMuta, std::string metSel, double rateSel, int numEval, double winVal, double drawVal, int randSeed) : m_sizePopulation(sizePop), 
	m_sizeStrategy(sizePort), m_distributionStrategy(distPort), m_numGenerations(numGen), m_methodMutation(metMuta), m_rateMutation(rateMuta),
	m_methodSelection(metSel), m_rateSelection(rateSel), m_numEvals(numEval), m_winVal(winVal), m_drawVal(drawVal), m_randSeed(randSeed)
{
	setMutator(metMuta); 
	setSelector(metSel); 
	setupPopulation(); 
	m_LineOfDescent.setup(m_population); 
}

void PopulationController::run(){
	for (int i = 0; i < m_numGenerations; i++){
		std::cout << "Generation: " << i+1 << std::endl;
		std::vector<Strategy> temp = m_Selector->createNextGen(m_population); 
		temp = m_Mutator->mutate_all(temp); 
		m_LineOfDescent.addGen(temp); 
		m_population = temp; 
	}
}

void PopulationController::outputData(std::string outputFilePath){
	std::string LODOut = outputFilePath; 
	std::string PopulationOut = outputFilePath; 
	LODOut += "LinesOfDescent/";
	LODOut += getFilePrefix(); 
	LODOut += "-LOD.txt"; 

	PopulationOut += "Populations/";
	PopulationOut += getFilePrefix();
	PopulationOut += "-POP.txt";


	std::string testingOut = outputFilePath;
	testingOut += getFilePrefix();
	testingOut += "-TESTDATA.txt";

	std::ofstream Popfile(PopulationOut);
	if (Popfile.is_open()){
		Popfile << getFilePrefix() << "\n";
		Popfile << populationToString();
		Popfile.close();
	} else {
		std::cout << "Could not open " << PopulationOut << std::endl;
	}

	std::ofstream testingfile(testingOut);
	if (testingfile.is_open())
	{
		testingfile << getFilePrefix() << "\n";
		testingfile << "ID, winsVsPerfect, drawsVsPerfect, winsVsRandom, drawsVsRandom, winsVsPopulation, drawsVsPopulation\n";
		for (auto p : finalTesting()) {
			testingfile << p.first;
			for (auto val : p.second) {
				testingfile << ", " << val;
			}
			testingfile << "\n";
		}
		testingfile.close();
	}
	else {
		std::cout << "Could not open " << testingOut << std::endl;
	}

	std::ofstream LODfile(LODOut);
	if (LODfile.is_open())
	{
		LODfile << getFilePrefix() << "\n";
		LODfile << m_LineOfDescent.printLineOfDescent();
		LODfile.close();
	}
	else {
		std::cout << "Could not open " << LODOut << std::endl;
	}
}

void PopulationController::setMutator(std::string metMuta){
	if (metMuta == "point"){
		m_methodMutation = metMuta; 
		m_Mutator = new PointMutator(m_rateMutation, m_sizeStrategy); 
	} else {
		std::cout << "NO MUTATOR ASSIGNED" << std::endl;
	}
	
}

void PopulationController::setSelector(std::string metSel){
	if (metSel == "elite"){
		m_methodSelection = metSel; 
		m_Selector = new EliteSelector(m_rateSelection, m_numEvals,m_winVal, 0.0, m_drawVal); 
	} else if (metSel == "roulette") {
		m_methodSelection = metSel;
		m_Selector = new RouletteSelector(m_rateSelection, m_numEvals, m_winVal, 0.0, m_drawVal);
	} else {
		std::cout << "NO SELECTOR ASSIGNED" << std::endl;
	}
}

void PopulationController::setupPopulation(){ 
	if(m_distributionStrategy == "uniform"){
		int genIDctr = 1; 
		while(m_population.size() < m_sizePopulation){			
			Strategy p; 
			p.fitness = 0.0; 
			p.generation = 0; 
			p.generationID = genIDctr; 
			genIDctr++; 
			p.parentID = -1; 
			
			for(size_t i = 0; i < m_sizeStrategy; i++){
				p.PlayArray.push_back(1); 
			}

			m_population.push_back(p); 
		}
	} else if (m_distributionStrategy == "random") {
		int genIDctr = 1;
		while (m_population.size() < m_sizePopulation) {
			Strategy p;
			p.fitness = 0.0;
			p.generation = 0;
			p.generationID = genIDctr;
			genIDctr++;
			p.parentID = -1;

			for (size_t i = 0; i < m_sizeStrategy; i++) {
				p.PlayArray.push_back(Random::getInt(0,8));
			}

			m_population.push_back(p);
		}
	} else {
		std::cout << "NO POPULATION GENERATION ASSIGNED" << std::endl;
	}

}

std::string PopulationController::getFilePrefix(){
	std::string outString = "Strategys-"; 
	outString += std::to_string(m_sizePopulation); 
	outString += "-";
	outString += std::to_string(m_numGenerations);
	outString += "-";
	outString += std::to_string(m_rateMutation);
	outString += "-";
	outString += m_methodSelection;
	outString += "-";
	outString += std::to_string(m_rateSelection);
	outString += "-";
	outString += std::to_string(m_winVal);
	outString += "-";
	outString += std::to_string(m_drawVal); 
	outString += "-";
	outString += std::to_string(m_randSeed);
	return outString; 
}

std::string PopulationController::populationToString(){
	std::string outString = ""; 
	for (std::vector<Strategy>::iterator it = m_population.begin(); it != m_population.end(); it++)
	{
		outString += it->toString();
	}

	return outString; 
}

std::map<std::string, std::vector<int>> PopulationController::finalTesting()
{
	TTTPlayer* myRandomPlayer = new TTTRandomPlayer(); 
	TTTPlayer* myPerfectPlayer = new TTTMinimaxPlayer(); 

	std::map<std::string, std::vector<int>> temp = std::map<std::string, std::vector<int>>(); 
	for (auto member : m_population) {
		int winsVsRandom = 0, winsVsPerfect = 0, winsVsPopulation = 0;
		int drawsVsRandom = 0, drawsVsPerfect = 0, drawsVsPopulation = 0;

		for (int i = 0; i < 100; i++) {
			int perfectResult = ((EliteSelector*)m_Selector)->play(member, myPerfectPlayer);
			int randomResult = ((EliteSelector*)m_Selector)->play(member, myRandomPlayer);
			int populationResult = ((EliteSelector*)m_Selector)->play(member, m_population.at(Random::getIndex(m_population.size())));
			if (perfectResult == 1) {
				winsVsPerfect++; 
			} else if (perfectResult == 0) {
				drawsVsPerfect++; 
			}
			if (randomResult == 1) {
				winsVsRandom++;
			}
			else if (randomResult == 0) {
				drawsVsRandom++;
			}
			if (populationResult == 1) {
				winsVsPopulation++;
			}
			else if (populationResult == 0) {
				drawsVsPopulation++;
			}
		}

		std::vector<int> results = std::vector<int>(); 
		results.push_back(winsVsPerfect);
		results.push_back(drawsVsPerfect);
		results.push_back(winsVsRandom);
		results.push_back(drawsVsRandom);
		results.push_back(winsVsPopulation);
		results.push_back(drawsVsPopulation);
		temp[member.getIDString()] = results; 
	}

	return temp;
}
