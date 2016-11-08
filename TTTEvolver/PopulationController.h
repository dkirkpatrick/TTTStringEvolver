/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#ifndef POPULATIONCONTROLLER_H_   
#define POPULATIONCONTROLLER_H_

#include "Mutator.h"
#include "Selector.h"
#include "LineOfDescentManager.h"
#include <string>
#include <map>

class PopulationController{
public:
	PopulationController(int sizePop, int sizePort, std::string distPort, int numGen, int outIntvl,
			std::string outPath, std::string metMuta, double rateMuta, std::string metSel, double rateSel, 
			int numEval, double winVal, double drawVal, int randSeed, bool strtAdvtg, int gamesVsRand);
	void run();
	void outputData(int numGeneration); 
	void setMutator(std::string metMuta); 
	void setSelector(std::string metSel);
	std::string getFilePrefix(); 
	std::string populationToString(); 
	const std::vector<Strategy> getPopulation() {
		return m_population;
	};
	std::map<std::string, std::vector<int>> finalTesting(); 

private: 
	void setupPopulation(); 
	size_t m_sizePopulation;
	size_t m_sizeStrategy;
	std::string m_distributionStrategy;
	int m_numGenerations;
	std::string m_methodMutation;
	double m_rateMutation;
	std::string m_methodSelection;
	double m_rateSelection;
	int m_numEvals;
	double m_winVal; 
	double m_drawVal; 
	int m_randSeed; 
	std::string m_outfilePath; 
	int m_outputInterval;
	bool m_startAdvantage; 
	int m_gamesVsRandom; 

	std::vector<Strategy> m_population; 
	
	Mutator* m_Mutator; 
	Selector* m_Selector; 
	LineOfDescent m_LineOfDescent; 
};

#endif