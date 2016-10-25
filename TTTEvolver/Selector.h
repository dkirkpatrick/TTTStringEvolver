#ifndef Selector_H_
#define Selector_H_

#include <vector> 
#include "StructHeader.h"
#include <algorithm> 

class Selector{
public: 
	Selector(double rateSel, int numEval); 

	virtual std::vector<Strategy> createNextGen(std::vector<Strategy> oldGeneration) = 0; 

protected: 
	double m_rateSelection;
	int m_numEval; 
}; 


#endif