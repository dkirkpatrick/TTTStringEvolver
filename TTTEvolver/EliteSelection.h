/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#ifndef EliteSelection_H_
#define EliteSelection_H_

#include "Selector.h"
#include "TTTEngine.h"
#include "BoardDictionary.h"
#include "TTTPlayers.h"

class EliteSelector : public Selector{
public:
	EliteSelector(double rateSel, int numEval, double winVal, double lossVal, double drawVal, bool strtAdvtg, int gamesVsRand);
	std::vector<std::shared_ptr<Strategy>> createNextGen(std::vector<std::shared_ptr<Strategy>>& oldGeneration);
};


#endif