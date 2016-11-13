/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#include "RouletteSelection.h"
#include "Random.h"
#include <iostream>

RouletteSelector::RouletteSelector(double rateSel, int numEval, double winVal, double lossVal, double drawVal, bool strtAdvtg, int gamesVsRand) : 
	Selector(rateSel, numEval,  winVal,  lossVal, drawVal, strtAdvtg, gamesVsRand) {
	myRef = BoardDictionary();
	m_randomPlayer = new TTTRandomPlayer();
	m_perfectPlayer = new TTTMinimaxPlayer();
}

std::vector<std::shared_ptr<Strategy>> RouletteSelector::createNextGen(std::vector<std::shared_ptr<Strategy>>& oldGeneration) {
	double maxFitness = 0.0; 
	std::vector<double> fitnessArray = std::vector<double>(oldGeneration.size(), 0.0); 
	for(int i = 0; i < oldGeneration.size(); i++){
		for (int j = 0; j < oldGeneration.size(); j++) {
			double value = play(oldGeneration[i], oldGeneration[j], 1);
			if (value > 0) {
				fitnessArray[i] += m_winVal;
				oldGeneration[i]->win++;
				oldGeneration[i]->winPop++;
			}
			else if (value < 0) {
				fitnessArray[i] += m_lossVal;
				oldGeneration[i]->loss++;
				oldGeneration[i]->lossPop++;
			}
			else {
				fitnessArray[i] += m_drawVal;
				oldGeneration[i]->draw++;
				oldGeneration[i]->drawPop++;
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

		double game1 = play(oldGeneration[i], m_perfectPlayer, 1);
		double game2 = play(oldGeneration[i], m_perfectPlayer, 2);
		if (game1 > 0) {
			oldGeneration[i]->winPerf++;
		} else if (game1 < 0) {
			oldGeneration[i]->lossPerf++;
		} else {
			oldGeneration[i]->drawPerf++;
		}
		if (game2 > 0) {
			oldGeneration[i]->winPerf++;
		}
		else if (game2 < 0) {
			oldGeneration[i]->lossPerf++;
		}
		else {
			oldGeneration[i]->drawPerf++;
		}
		
	}
	int n = 0, who = 0; 
	for (double d : fitnessArray) {
		if (maxFitness < d) {
			maxFitness = d;
			who = n; 
		}
		n++; 
	}
	std::shared_ptr<Strategy> p = oldGeneration.at(who); 
	std::cout << "MaxFitness: " << maxFitness << "   " << "StrategyID: " << who << "   " << "Losses/Draws/Wins:" << p->loss << '/' << p->draw << '/' << p->win << std::endl;

	std::vector<std::shared_ptr<Strategy>> newGeneration;

	int genIDcoutner = 0;

	while (newGeneration.size() < oldGeneration.size()) {
		int who;
		if (maxFitness > 0.0) {  // if anyone has fitness > 0
			do {
				who = Random::getIndex(oldGeneration.size());  //keep choosing a random genome from population until we get one that's good enough
			} while (pow(1.05, Random::getDouble(1)) > pow(1.05, (fitnessArray[who] / maxFitness)));
		}
		else {
			who = Random::getIndex(oldGeneration.size());  // otherwise, just pick a random genome from population
		}
		std::shared_ptr<Strategy> parent = oldGeneration.at(who);
		newGeneration.push_back(std::make_shared<Strategy>(parent, genIDcoutner));
		genIDcoutner++;

	}

	
	return newGeneration;
}