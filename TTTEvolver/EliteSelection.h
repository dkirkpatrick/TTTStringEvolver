#ifndef EliteSelection_H_
#define EliteSelection_H_

#include "Selector.h"

class EliteSelector : public Selector{
public:
	EliteSelector(double rateSel, int numEval);
	
	std::vector<Portfolio> createNextGen(std::vector<Portfolio> oldGeneration); 
};


#endif