/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#include "RouletteSelection.h"
#include "Random.h"
#include <iostream>

RouletteSelector::RouletteSelector(double rateSel, int numEval) : Selector(rateSel, numEval) {
	myRef = BoardDictionary();
	m_winVal = 1.0;
	m_lossVal = 0.0;
	m_drawVal = 1.0;
}

RouletteSelector::RouletteSelector(double rateSel, int numEval, double winVal, double lossVal, double drawVal, bool strtAdvtg) : 
	Selector(rateSel, numEval), m_lossVal(lossVal), m_winVal(winVal), m_drawVal(drawVal), m_startAdvantage(strtAdvtg) {
	myRef = BoardDictionary();
}

std::vector<Strategy> RouletteSelector::createNextGen(std::vector<Strategy> oldGeneration) {
	double maxFitness = 0.0; 
	std::vector<double> fitnessArray = std::vector<double>(oldGeneration.size(), 0.0); 
	for (Strategy p : oldGeneration) {
		for (Strategy p2 : oldGeneration) {
			double value = play(p, p2);
			if (value > 0) {
				fitnessArray[p.generationID-1] += m_winVal;
				fitnessArray[p2.generationID-1] += m_lossVal;
			}
			else if (value < 0) {
				fitnessArray[p.generationID-1] += m_lossVal;
				fitnessArray[p2.generationID-1] += m_winVal;
			}
			else {
				fitnessArray[p.generationID-1] += m_drawVal;
				fitnessArray[p2.generationID-1] += m_drawVal;
			}
		}
		p.setFitness(fitnessArray[p.generationID-1]); 
	}

	for (double d : fitnessArray) {
		if (maxFitness < d) {
			maxFitness = d;
		}
	}

	std::vector<Strategy> newGeneration;

	int genIDcoutner = 1;

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
		Strategy parent = oldGeneration.at(who);
		newGeneration.push_back(getChild(parent, genIDcoutner));
		genIDcoutner++;

	}

	return newGeneration;
}


int RouletteSelector::play(Strategy& s1, TTTPlayer* myPlayer) {
	int playCount = 0;
	TTTGame myGame = TTTGame(3);

	if (m_startAdvantage) {
		myGame.play(4, 1);
	}

	// Assign player to brain, opponent
	int s1Plays = Random::getInt(1, 2);
	int TTTPlayerPlays = (s1Plays == 2 ? 1 : 2);
	bool whoPlays = (TTTPlayerPlays == 1);
	int i = 0;
	// Handles the result until a conclusion is reached 
	while (myGame.gameWon() == 0 && !myGame.gameDraw() && i < 18) {
		i++;
		if (whoPlays) {
			std::vector<int> otherPlay = myPlayer->getPlay(myGame, TTTPlayerPlays);
			myGame.play(otherPlay.at(0), otherPlay.at(1), TTTPlayerPlays);
			whoPlays = false;
		}
		else {
			int myPlay = getPlay(s1, myGame, s1Plays);
			myGame.play(myPlay, s1Plays);
			whoPlays = true;
		}
	}

	// Outputs based on game results 
	if (myGame.gameDraw()) {
		return 0;
	}
	else if (myGame.gameWon() == s1Plays) {
		return 1;
	}
	else {
		return -1;
	}
}

int RouletteSelector::play(Strategy& s1, Strategy& s2) {
	int playCount = 0;
	TTTGame myGame = TTTGame(3);

	if (m_startAdvantage) {
		myGame.play(4, 1); 
	}

	// Assign player to brain, opponent
	int s1Plays = 1;
	int s2Plays = (s1Plays == 2 ? 1 : 2);
	bool whoPlays = (s2Plays == 1);
	int i = 0;
	// Handles the result until a conclusion is reached 
	while (myGame.gameWon() == 0 && !myGame.gameDraw() && i < 18) {
		i++;
		if (whoPlays) {
			int otherPlay = getPlay(s2, myGame, s2Plays);
			myGame.play(otherPlay, s2Plays);
			whoPlays = false;
		}
		else {
			int myPlay = getPlay(s1, myGame, s1Plays);
			myGame.play(myPlay, s1Plays);
			whoPlays = true;
		}
	}

	// Outputs based on game results 
	if (myGame.gameDraw()) {
		return 0;
	}
	else if (myGame.gameWon() == s1Plays) {
		return 1;
	}
	else {
		return -1;
	}
}

int RouletteSelector::getPlay(Strategy& s, TTTGame& mGame, int whichPlayer)
{
	std::vector<int> lookup = myRef.dict().at(mGame.base3Board());
	std::vector<int> permute = mGame.getInversePermutation(myRef.getMask(lookup.at(1)));
	int offset = (whichPlayer == 1) ? 0 : 1582;
	return permute.at(s.PlayArray.at(lookup.at(2) + offset));
}