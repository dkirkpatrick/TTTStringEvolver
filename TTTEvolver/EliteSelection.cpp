/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#include "EliteSelection.h"
#include "Random.h"
#include <iostream>

EliteSelector::EliteSelector(double rateSel, int numEval, double winVal, double lossVal, double drawVal, bool strtAdvtg, int gamesVsRand): 
	Selector(rateSel, numEval, winVal, lossVal, drawVal, strtAdvtg, gamesVsRand) {
	myRef = BoardDictionary();
}

std::vector<std::shared_ptr<Strategy>> EliteSelector::createNextGen(std::vector<std::shared_ptr<Strategy>>& oldGeneration){
	std::vector<double> fitnessArray = std::vector<double>(oldGeneration.size(), 0.0);
	for (int i = 0; i < oldGeneration.size(); i++) {
		for (int j = 0; j < oldGeneration.size(); j++) {
			double value = play(oldGeneration[i], oldGeneration[j]);
			if (value > 0) {
				fitnessArray[i] += m_winVal;
				fitnessArray[j] += m_lossVal;
				oldGeneration[i]->win++;
				oldGeneration[j]->loss++;
				oldGeneration[i]->winPop++;
				oldGeneration[j]->lossPop++;

			}
			else if (value < 0) {
				fitnessArray[i] += m_lossVal;
				fitnessArray[j] += m_winVal;
				oldGeneration[i]->loss++;
				oldGeneration[j]->win++;
				oldGeneration[i]->lossPop++;
				oldGeneration[j]->winPop++;
			}
			else {
				fitnessArray[i] += m_drawVal;
				fitnessArray[j] += m_drawVal;
				oldGeneration[i]->draw++;
				oldGeneration[j]->draw++;
				oldGeneration[i]->drawPop++;
				oldGeneration[j]->drawPop++;
			}
		}

		for (int j = 0; j < m_gamesVsRandom; j++) {
			double value = play(oldGeneration[i], m_randomPlayer, Random::getInt(1, 2));
			if (value > 0) {
				fitnessArray[i] += m_winVal;
				oldGeneration[i]->win++;
				oldGeneration[i]->winRand++;
			}
			else if (value < 0) {
				fitnessArray[i] += m_lossVal;
				oldGeneration[i]->loss++;
				oldGeneration[i]->lossRand++;
			}
			else {
				fitnessArray[i] += m_drawVal;
				oldGeneration[i]->draw++;
				oldGeneration[i]->drawRand++;
			}
		}

	}

	for (int i = 0; i < oldGeneration.size(); i++) {
		oldGeneration[i]->fitness = fitnessArray[i];
	}

	std::sort(oldGeneration.begin(), oldGeneration.end()); 
	std::reverse(oldGeneration.begin(),oldGeneration.end()); 

	int populationProportion = (int) std::ceil(m_rateSelection*oldGeneration.size()); 

	std::vector<std::shared_ptr<Strategy>> newGeneration;

	int genIDcoutner = 1; 

	while(newGeneration.size() < oldGeneration.size()){
		int selectionVar  = Random::getIndex(populationProportion);
		std::shared_ptr<Strategy> parent = oldGeneration.at(selectionVar);
		newGeneration.push_back(std::make_shared<Strategy>(parent, genIDcoutner));
		genIDcoutner++;
	}

	return newGeneration; 
}