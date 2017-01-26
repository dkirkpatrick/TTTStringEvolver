/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#ifndef Selector_H_
#define Selector_H_

#include <vector> 
#include "StructHeader.h"
#include <algorithm> 
#include "TTTEngine.h"
#include "BoardDictionary.h"
#include "TTTPlayers.h"

class Selector{
public: 
	Selector(double rateSel, int numEval, double winVal, double lossVal, double drawVal, bool strtAdvtg, int gamesVsRand);

	virtual std::vector<std::shared_ptr<Strategy>> createNextGen(std::vector<std::shared_ptr<Strategy>>& oldGeneration) = 0;

	int play(std::shared_ptr<Strategy> s1, std::shared_ptr<Strategy> s2, int startPlayer);
	int play(std::shared_ptr<Strategy> s1, TTTPlayer * myPlayer, int startPlayer);
	int playWithDistribution(std::shared_ptr<Strategy> s1, TTTPlayer* myPlayer, int startPlayer, std::map<int, int>& playDistribution);
	int playWithDistribution(std::shared_ptr<Strategy> s1, std::shared_ptr<Strategy> s2, int startPlayer, std::map<int, int>& playDistribution);
	int getPlay(std::shared_ptr<Strategy> s, TTTGame& mGame, int whichPlayer);

	BoardDictionary& getDictionary() {
		return myRef; 
	}

protected: 
	double m_rateSelection;
	int m_numEval; 
	bool m_startAdvantage;
	BoardDictionary myRef;
	double m_winVal;
	double m_lossVal;
	double m_drawVal;
	TTTPlayer* m_randomPlayer;
	TTTPlayer* m_perfectPlayer;
	int m_gamesVsRandom;
}; 


#endif