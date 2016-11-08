/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#ifndef RouletteSelection_H_
#define RouletteSelection_H_

#include "Selector.h"
#include "TTTEngine.h"
#include "BoardDictionary.h"
#include "TTTPlayers.h"

class RouletteSelector : public Selector {
public:
	RouletteSelector(double rateSel, int numEval);
	RouletteSelector(double rateSel, int numEval, double winVal, double lossVal, double drawVal, bool strtAdvtg);
	std::vector<Strategy> createNextGen(std::vector<Strategy> oldGeneration);

	int play(Strategy& s1, Strategy& s2);
	int play(Strategy& s1, TTTPlayer * myPlayer);
	int getPlay(Strategy& s, TTTGame& mGame, int whichPlayer);

private:
	BoardDictionary myRef;
	double m_winVal;
	double m_lossVal;
	double m_drawVal;
	bool m_startAdvantage; 
};


#endif