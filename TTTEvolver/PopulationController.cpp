#include "PopulationController.h"
#include "RandomAddMutator.h"
#include "RandomSubtractMutator.h"
#include "ReallocationMutator.h"
#include "EliteSelection.h"
#include <iostream>
#include <fstream>

PopulationController::PopulationController(int sizePop, int sizePort, std::string distPort, int numGen, std::string metMuta,
	double rateMuta, std::string metSel, double rateSel, int numEval):m_sizePopulation(sizePop), m_sizePortfolio(sizePort), 
	m_distributionPortfolio(distPort), m_numGenerations(numGen), m_methodMutation(metMuta), m_rateMutation(rateMuta), 
	m_methodSelection(metSel), m_rateSelection(rateSel), m_numEvals(numEval)
{
	setMutator(metMuta); 
	setSelector(metSel); 
	setupPopulation(); 
	m_LineOfDescent.setup(m_population); 
}

void PopulationController::run(){
	for (int i = 0; i < m_numGenerations; i++){
		std::vector<Portfolio> temp = m_Selector->createNextGen(m_population); 
		temp = m_Mutator->mutate_all(temp); 
		m_LineOfDescent.addGen(temp); 
		m_population = temp; 
	}
}

void PopulationController::outputData(std::string outputFilePath){
	std::string LODOut = outputFilePath; 
	std::string PopulationOut = outputFilePath; 
	LODOut += "\\LinesOfDescent\\";
	LODOut += getFilePrefix(); 
	LODOut += "-LOD.txt"; 

	PopulationOut += "\\Populations\\";
	PopulationOut += getFilePrefix();
	PopulationOut += "-POP.txt";

	std::ofstream Popfile(PopulationOut);
	if (Popfile.is_open()){
		Popfile << getFilePrefix() << "\n";
		Popfile << populationToString();
		Popfile.close();
	}

	std::ofstream LODfile(LODOut);
	if (LODfile.is_open())
	{
		LODfile << getFilePrefix() << "\n";
		//TODO: FIX LINE OF DESCENT OUTPUT
		LODfile << m_LineOfDescent.printLineOfDescent();
		LODfile.close();
	}
}

void PopulationController::setMutator(std::string metMuta){
	if (metMuta == "randomAdd"){
		m_methodMutation = metMuta; 
		m_Mutator = new RandomAddMutator(m_rateMutation, m_sizePortfolio); 
	}
}

void PopulationController::setSelector(std::string metSel){
	if (metSel == "elite"){
		m_methodSelection = metSel; 
		m_Selector = new EliteSelector(m_rateSelection, m_numEvals); 
	}
}

void PopulationController::setupPopulation(){ 
	if(m_distributionPortfolio == "uniform"){
		int genIDctr = 1; 
		while(m_population.size() < m_sizePopulation){			
			Portfolio p; 
			p.fitness = 0.0; 
			p.generation = 0; 
			p.generationID = genIDctr; 
			genIDctr++; 
			p.parentID = -1; 
			
			for(size_t i = 0; i < m_sizePortfolio; i++){
				p.ValueArray.push_back(1.0); 
			}

			m_population.push_back(p); 
		}
	}
}

std::string PopulationController::getFilePrefix(){
	std::string outString = "Portfolios-"; 
	outString += std::to_string(m_sizePopulation); 
	outString += "-"; 
	outString += std::to_string(m_sizePortfolio);
	outString += "-";
	outString += m_distributionPortfolio; 
	outString += "-";
	outString += std::to_string(m_numGenerations);
	outString += "-";
	outString += m_methodMutation;
	outString += "-";
	outString += std::to_string(m_rateMutation);
	outString += "-";
	outString += m_methodSelection;
	outString += "-";
	outString += std::to_string(m_rateSelection);
	outString += "-";
	outString += std::to_string(m_numEvals);

	return outString; 
}

std::string PopulationController::populationToString(){
	std::string outString = ""; 
	for (std::vector<Portfolio>::iterator it = m_population.begin(); it != m_population.end(); it++)
	{
		outString += it->toString();
	}

	return outString; 
}