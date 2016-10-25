#ifndef POPULATIONCONTROLLER_H_   
#define POPULATIONCONTROLLER_H_

#include "Mutator.h"
#include "Selector.h"
#include "LineOfDescentManager.h"
#include <string>

class PopulationController{
public:
	PopulationController(int sizePop, int sizePort, std::string distPort, int numGen, std::string metMuta,
		double rateMuta, std::string metSel, double rateSel, int numEval);
	void run(); 
	void outputData(std::string outputFilePath); 
	void setMutator(std::string metMuta); 
	void setSelector(std::string metSel);
	std::string getFilePrefix(); 
	std::string populationToString(); 

private: 
	void setupPopulation(); 
	size_t m_sizePopulation;
	size_t m_sizePortfolio;
	std::string m_distributionPortfolio;
	int m_numGenerations;
	std::string m_methodMutation;
	double m_rateMutation;
	std::string m_methodSelection;
	double m_rateSelection;
	int m_numEvals;

	std::vector<Portfolio> m_population; 
	
	Mutator* m_Mutator; 
	Selector* m_Selector; 
	LineOfDescent m_LineOfDescent; 
};

#endif