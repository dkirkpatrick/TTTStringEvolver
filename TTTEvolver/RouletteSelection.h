/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#ifndef RouletteSelection_H_
#define RouletteSelection_H_

#include "Selector.h"

class RouletteSelector : public Selector {
public:
	RouletteSelector(double rateSel, int numEval, double winVal, double lossVal, double drawVal, bool strtAdvtg, int gamesVsRand);
	std::vector<std::shared_ptr<Strategy>> createNextGen(std::vector<std::shared_ptr<Strategy>>& oldGeneration);
};


#endif