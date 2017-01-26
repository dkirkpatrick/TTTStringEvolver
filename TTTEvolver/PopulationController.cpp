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
#include "ValidPointMutator.h"
#include "BoardDictionary.h"

PopulationController::PopulationController(int sizePop, std::vector<int> whichMasks, std::string distPort, int numGen, int outIntvl, std::string outPath, std::string metMuta,
	double rateMuta, std::string metSel, double rateSel, int numEval, double winVal, double drawVal, int randSeed, bool strtAdvtg, int gamesVsRand) : m_sizePopulation(sizePop),
	m_distributionStrategy(distPort), m_numGenerations(numGen), m_methodMutation(metMuta), m_rateMutation(rateMuta), m_outputInterval(outIntvl),
	m_methodSelection(metSel), m_rateSelection(rateSel), m_numEvals(numEval), m_winVal(winVal), m_drawVal(drawVal), m_randSeed(randSeed), m_outfilePath(outPath), 
	m_startAdvantage(strtAdvtg), m_gamesVsRandom(gamesVsRand)
{
	setMutator(metMuta); 
	setSelector(metSel); 
	setupPopulation(whichMasks); 
}

void PopulationController::run(){
	outputData(0);
	for (int i = 0; i < m_numGenerations; i++){
		std::cout << "Generation: " << i+1 << std::endl;
		std::vector<std::shared_ptr<Strategy>> temp = m_Selector->createNextGen(m_population); 
		for (int i = 0; i < m_population.size(); i++) {
			m_population.erase(m_population.begin());
		}
		m_population = temp; 
		if ((i+1)%m_outputInterval == 0) {
			outputData(i+1);
		}
	}
}

void PopulationController::runLODOnly() {
	for (int i = 0; i < m_numGenerations; i++) {
		std::cout << "Generation: " << i + 1 << std::endl;
		std::vector<std::shared_ptr<Strategy>> temp = m_Selector->createNextGen(m_population);
		for (int i = 0; i < m_population.size(); i++) {
			m_population.erase(m_population.begin());
		}
		m_population = temp;
	}
	m_Selector->createNextGen(m_population);
	std::string LODOut = m_outfilePath;
	std::string PopulationOut = m_outfilePath;
	LODOut += "LinesOfDescent/";
	LODOut += getFilePrefix();
	LODOut += "-";
	LODOut += std::to_string(m_numGenerations);
	LODOut += "-LOD.txt";
	std::ofstream LODfile(LODOut);
	if (LODfile.is_open())
	{
		LODfile << "ID, win, loss, draw, winPop, lossPop, drawPop, winRand, lossRand, drawRand, winPerf, lossPerf, drawPerf\n";
		LODfile << printLineOfDescent();
		LODfile.close();
	}
	else {
		std::cout << "Could not open " << LODOut << std::endl;
	}
}

void PopulationController::runLODandDistributions() {
	for (int i = 0; i < m_numGenerations; i++) {
		std::cout << "Generation: " << i + 1 << std::endl;
		std::vector<std::shared_ptr<Strategy>> temp = m_Selector->createNextGen(m_population);
		for (int i = 0; i < m_population.size(); i++) {
			m_population.erase(m_population.begin());
		}
		m_population = temp;
	}
	m_Selector->createNextGen(m_population);

	TTTPlayer* mRandomPlayer = new TTTRandomPlayer(); 
	std::map<int, int> myDistribution1;
	std::map<int, int> myDistribution2;
	for (int i : m_Selector->getDictionary().getValidBoards()) {
		myDistribution1[i] = 0;
		myDistribution2[i] = 0;
	}
	for (auto member : m_population) {
		for (int i = 0; i < 2500; i++) {
			m_Selector->playWithDistribution(member, mRandomPlayer, 1, myDistribution1);
			m_Selector->playWithDistribution(member, mRandomPlayer, 2, myDistribution2);
		}
	}

	std::string DistributionsOut1 = m_outfilePath + "Distributions/" + getFilePrefix() + "-PopVsRandDist.csv";
	std::string DistributionsOut2 = m_outfilePath + "Distributions/" + getFilePrefix() + "-RandVsPopDist.csv";

	std::ofstream DistributionsFile1(DistributionsOut1);
	if (DistributionsFile1.is_open())
	{
		DistributionsFile1 << "Board, FrequencyCount\n";
		for (auto item : myDistribution1) {
			DistributionsFile1 << item.first << "," << item.second << "\n";
		}
	}

	std::ofstream DistributionsFile2(DistributionsOut2);
	if (DistributionsFile2.is_open())
	{
		DistributionsFile2 << "Board, FrequencyCount\n";
		for (auto item : myDistribution2) {
			DistributionsFile2 << item.first << "," << item.second << "\n";
		}
	}

	std::string LODOut = m_outfilePath;
	std::string PopulationOut = m_outfilePath;
	LODOut += "LinesOfDescent/";
	LODOut += getFilePrefix();
	LODOut += "-";
	LODOut += std::to_string(m_numGenerations);
	LODOut += "-LOD.txt";
	std::ofstream LODfile(LODOut);
	if (LODfile.is_open())
	{
		LODfile << "ID, win, loss, draw, winPop, lossPop, drawPop, winRand, lossRand, drawRand, winPerf, lossPerf, drawPerf\n";
		LODfile << printLineOfDescent();
		LODfile.close();
	}
	else {
		std::cout << "Could not open " << LODOut << std::endl;
	}
}


void PopulationController::outputData(int numGeneration){
	std::string LODOut = m_outfilePath;
	std::string PopulationOut = m_outfilePath;
	LODOut += "LinesOfDescent/";
	LODOut += getFilePrefix(); 
	LODOut += "-"; 
	LODOut += std::to_string(numGeneration);
	LODOut += "-LOD.txt"; 

	PopulationOut += "Populations/";
	PopulationOut += getFilePrefix();
	PopulationOut += "-";
	PopulationOut += std::to_string(numGeneration);
	PopulationOut += "-POP.txt";


	std::string testingOut = m_outfilePath;
	testingOut += getFilePrefix();
	testingOut += "-";
	testingOut += std::to_string(numGeneration);
	testingOut += "-TESTDATA.csv";

	std::ofstream Popfile(PopulationOut);
	if (Popfile.is_open()){
		Popfile << getFilePrefix() << "-" << numGeneration << "\n";
		Popfile << populationToString();
		Popfile.close();
	} else {
		std::cout << "Could not open " << PopulationOut << std::endl;
	}

	std::ofstream testingfile(testingOut);
	if (testingfile.is_open())
	{
		testingfile << getFilePrefix() << "-" << numGeneration << "\n";
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
	if (numGeneration == m_numGenerations) {
		std::ofstream LODfile(LODOut);
		if (LODfile.is_open())
		{
			LODfile << getFilePrefix() << "-" << numGeneration << "\n";
			LODfile << printLineOfDescent();
			LODfile.close();
		}
		else {
			std::cout << "Could not open " << LODOut << std::endl;
		}
	}
}

void PopulationController::setMutator(std::string metMuta){
	if (metMuta == "point"){
		m_methodMutation = metMuta; 
		m_Mutator = new PointMutator(m_rateMutation, m_sizeStrategy); 
	} else if (metMuta == "validPoint") {
		m_methodMutation = metMuta;
		m_Mutator = new ValidPointMutator(m_rateMutation, m_sizeStrategy);
	} else {
		std::cout << "NO MUTATOR ASSIGNED" << std::endl;
	}
	
}

void PopulationController::setSelector(std::string metSel){
	if (metSel == "elite"){
		m_methodSelection = metSel; 
		m_Selector = new EliteSelector(m_rateSelection, m_numEvals, m_winVal, 0.0, m_drawVal, m_startAdvantage, m_gamesVsRandom);
	} else if (metSel == "roulette") {
		m_methodSelection = metSel;
		m_Selector = new RouletteSelector(m_rateSelection, m_numEvals, m_winVal, 0.0, m_drawVal, m_startAdvantage, m_gamesVsRandom);
	} else {
		std::cout << "NO SELECTOR ASSIGNED" << std::endl;
	}
}

void PopulationController::setupPopulation(std::vector<int> whichMasks) {
	int genIDctr = 0;
	BoardDictionary myRef = BoardDictionary(whichMasks); 
	m_sizeStrategy = myRef.getReducedSize() * 2; 
	while (m_population.size() < m_sizePopulation) {
		m_population.push_back(std::make_shared<Strategy>(m_distributionStrategy, genIDctr, m_sizeStrategy, myRef, m_Mutator));
	}
}

std::string PopulationController::getFilePrefix(){
	std::string outString = "Strategies-p"; 
	outString += std::to_string(m_sizePopulation); 
	outString += "-g";
	outString += std::to_string(m_numGenerations);
	outString += "-rM";
	outString += std::to_string(m_rateMutation);
	outString += "-";
	outString += m_methodSelection;
	outString += "-rS";
	outString += std::to_string(m_rateSelection);
	outString += "-w";
	outString += std::to_string(m_winVal);
	outString += "-d";
	outString += std::to_string(m_drawVal); 
	outString += "-gR";
	outString += std::to_string(m_gamesVsRandom);
	outString += "-sA";
	outString += std::to_string(m_startAdvantage);
	outString += "-s";
	outString += std::to_string(m_randSeed);
	return outString; 
}

std::string PopulationController::populationToString(){
	std::string outString = ""; 
	for (int i = 0; i < m_population.size(); i++)
	{
		outString += m_population[i]->toString();
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
		int lossesVsRandom = 0, lossesVsPerfect = 0, lossesVsPopulation = 0;

		for (int i = 0; i < 100; i++) {
			int perfectResult = ((RouletteSelector*)m_Selector)->play(member, myPerfectPlayer, Random::getInt(1, 2));
			int randomResult = ((RouletteSelector*)m_Selector)->play(member, myRandomPlayer, Random::getInt(1, 2));
			int populationResult = ((RouletteSelector*)m_Selector)->play(member, m_population.at(Random::getIndex(m_population.size())));
			if (perfectResult == 1) {
				winsVsPerfect++; 
			} else if (perfectResult == 0) {
				drawsVsPerfect++; 
			}
			else {
				lossesVsPerfect++;
			}
			if (randomResult == 1) {
				winsVsRandom++;
			}
			else if (randomResult == 0) {
				drawsVsRandom++;
			}
			else {
				lossesVsRandom++;
			}
			if (populationResult == 1) {
				winsVsPopulation++;
			}
			else if (populationResult == 0) {
				drawsVsPopulation++;
			} else {
				lossesVsPopulation++; 
			}
		}

		std::vector<int> results = std::vector<int>(); 
		results.push_back(winsVsPerfect);
		results.push_back(drawsVsPerfect);
		results.push_back(winsVsRandom);
		results.push_back(drawsVsRandom);
		results.push_back(winsVsPopulation);
		results.push_back(drawsVsPopulation);
		results.push_back(drawsVsPopulation);
		temp[member->getIDString()] = results; 
	}

	return temp;
}


std::string PopulationController::printLineOfDescent() {
	std::vector<std::shared_ptr<Strategy>> outputVector;
	std::shared_ptr<Strategy> processingQueue;
	std::string outputString = "";

	processingQueue = m_population[0];

	while (processingQueue->ancestor) {
		outputVector.push_back(processingQueue);
		processingQueue = processingQueue->ancestor;
	}

	std::reverse(outputVector.begin(), outputVector.end());

	for (int i = 0; i < outputVector.size(); i++)
	{
		outputString += outputVector[i]->toStringLOD();
	}

	return outputString;
}