#ifndef Mutator_H_
#define Mutator_H_

#include "StructHeader.h"
#include <vector>

class Mutator{
public:
	Mutator(double mutaRate); 

	std::vector<Portfolio> mutate_all(std::vector<Portfolio> mGeneration); 

	virtual Portfolio mutate(Portfolio temp) = 0; 

protected: 
	double m_mutationRate; 
};

#endif