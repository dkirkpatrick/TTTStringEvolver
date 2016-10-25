#include "EliteSelection.h"

EliteSelector::EliteSelector(double rateSel, int numEval) : Selector(rateSel, numEval){}

std::vector<Portfolio> EliteSelector::createNextGen(std::vector<Portfolio> oldGeneration){
	for(Portfolio p: oldGeneration){
		p.fitness = 0.0; 
		int portfolioSize = p.ValueArray.size(); 
		for(int i = 0; i < m_numEval; i++){
			int evalTemp = rand() % portfolioSize;
			p.fitness+=p.ValueArray.at(evalTemp); 
		}
	}

	std::sort(oldGeneration.begin(), oldGeneration.end()); 
	std::reverse(oldGeneration.begin(),oldGeneration.end()); 

	int populationProportion = (int) std::ceil(m_rateSelection*oldGeneration.size()); 

	std::vector<Portfolio> newGeneration; 

	int genIDcoutner = 1; 

	while(newGeneration.size() < oldGeneration.size()){
		int selectionVar  = rand() % populationProportion; 
		Portfolio parent = oldGeneration.at(selectionVar); 

		Portfolio child; 
		child.fitness = 0.0; 
		child.generation = parent.generation + 1; 
		for (std::vector<double>::iterator it = parent.ValueArray.begin(); it != parent.ValueArray.end(); it++)
		{
			child.ValueArray.push_back(*it);
		}
		child.parentID = parent.generationID; 
		child.generationID = genIDcoutner; 
		genIDcoutner++; 

		newGeneration.push_back(child); 
	}

	return newGeneration; 
}