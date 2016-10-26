/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#ifndef Mutator_H_
#define Mutator_H_

#include "StructHeader.h"
#include <vector>

class Mutator{
public:
	Mutator(double mutaRate); 

	std::vector<Strategy> mutate_all(std::vector<Strategy> mGeneration); 

	virtual Strategy mutate(Strategy temp) = 0; 

protected: 
	double m_mutationRate; 
};

#endif