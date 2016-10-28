/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#include "EliteSelection.h"
#include "Random.h"
#include <iostream>

EliteSelector::EliteSelector(double rateSel, int numEval) : Selector(rateSel, numEval){
	myRef = BoardDictionary();
	m_winVal = 1.0; 
	m_lossVal = 0.0; 
	m_drawVal = 1.0;
}

EliteSelector::EliteSelector(double rateSel, int numEval, double winVal, double lossVal, double drawVal): Selector(rateSel, numEval), m_lossVal(lossVal), m_winVal(winVal), m_drawVal(drawVal) {
	myRef = BoardDictionary();
}

std::vector<Strategy> EliteSelector::createNextGen(std::vector<Strategy> oldGeneration){
	std::vector<double> fitnessArray = std::vector<double>(oldGeneration.size(), 0.0);
	for (Strategy p : oldGeneration) {
		for (Strategy p2 : oldGeneration) {
			double value = play(p, p2);
			if (value > 0) {
				fitnessArray[p.generationID - 1] += m_winVal;
			}
			else if (value < 0) {
				fitnessArray[p.generationID - 1] += m_lossVal;
			}
			else {
				fitnessArray[p.generationID - 1] += m_drawVal;
			}
		}
		p.setFitness(fitnessArray[p.generationID - 1]);
	}

	std::sort(oldGeneration.begin(), oldGeneration.end()); 
	std::reverse(oldGeneration.begin(),oldGeneration.end()); 

	int populationProportion = (int) std::ceil(m_rateSelection*oldGeneration.size()); 

	std::vector<Strategy> newGeneration; 

	int genIDcoutner = 1; 

	while(newGeneration.size() < oldGeneration.size()){
		int selectionVar  = Random::getIndex(populationProportion);
		Strategy parent = oldGeneration.at(selectionVar); 
		newGeneration.push_back(getChild(parent, genIDcoutner));
		genIDcoutner++;
	}

	return newGeneration; 
}


int EliteSelector::play(Strategy& s1, TTTPlayer* myPlayer) {
	int playCount = 0;
	TTTGame myGame = TTTGame(3);

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

int EliteSelector::play(Strategy& s1, Strategy& s2) {
	int playCount = 0;
	TTTGame myGame = TTTGame(3);
	
	// Assign player to brain, opponent
	int s1Plays = Random::getInt(1, 2);
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

int EliteSelector::getPlay(Strategy& s, TTTGame& mGame, int whichPlayer)
{
	std::vector<int> lookup = myRef.dict().at(mGame.base3Board()); 
	std::vector<int> permute = mGame.getInversePermutation(myRef.getMask(lookup.at(1))); 
	int offset = (whichPlayer == 1) ? 0 : 1582; 
	return permute.at(s.PlayArray.at(lookup.at(2)+offset));
}
