/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#include "Selector.h"

Selector::Selector(double rateSel, int numEval) : m_rateSelection(rateSel), m_numEval(numEval) {}

Strategy Selector::getChild(Strategy parent, int genIDcoutner) {
	Strategy child;
	child.fitness = 0.0;
	child.generation = parent.generation + 1;
	for (std::vector<int>::iterator it = parent.PlayArray.begin(); it != parent.PlayArray.end(); it++)
	{
		child.PlayArray.push_back(*it);
	}
	child.parentID = parent.generationID;
	child.generationID = genIDcoutner;
	return child; 
}