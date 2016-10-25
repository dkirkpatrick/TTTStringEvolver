#include "EliteSelection.h"

EliteSelector::EliteSelector(double rateSel, int numEval) : Selector(rateSel, numEval){}

std::vector<Strategy> EliteSelector::createNextGen(std::vector<Strategy> oldGeneration){
	for(Strategy p: oldGeneration){
		p.fitness = 0.0; 
		int StrategySize = p.PlayArray.size(); 
		for(int i = 0; i < m_numEval; i++){
			int evalTemp = rand() % StrategySize;
			p.fitness+=p.PlayArray.at(evalTemp); 
		}
	}

	std::sort(oldGeneration.begin(), oldGeneration.end()); 
	std::reverse(oldGeneration.begin(),oldGeneration.end()); 

	int populationProportion = (int) std::ceil(m_rateSelection*oldGeneration.size()); 

	std::vector<Strategy> newGeneration; 

	int genIDcoutner = 1; 

	while(newGeneration.size() < oldGeneration.size()){
		int selectionVar  = rand() % populationProportion; 
		Strategy parent = oldGeneration.at(selectionVar); 

		Strategy child; 
		child.fitness = 0.0; 
		child.generation = parent.generation + 1; 
		for (std::vector<int>::iterator it = parent.PlayArray.begin(); it != parent.PlayArray.end(); it++)
		{
			child.PlayArray.push_back(*it);
		}
		child.parentID = parent.generationID; 
		child.generationID = genIDcoutner; 
		genIDcoutner++; 

		newGeneration.push_back(child); 
	}

	return newGeneration; 
}