/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#ifndef Selector_H_
#define Selector_H_

#include <vector> 
#include "StructHeader.h"
#include <algorithm> 

class Selector{
public: 
	Selector(double rateSel, int numEval);

	Strategy getChild(Strategy parent, int genIDcoutner);

	virtual std::vector<Strategy> createNextGen(std::vector<Strategy> oldGeneration) = 0; 

protected: 
	double m_rateSelection;
	int m_numEval; 
}; 


#endif