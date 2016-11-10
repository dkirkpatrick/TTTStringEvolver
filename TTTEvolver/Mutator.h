/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#ifndef Mutator_H_
#define Mutator_H_

#include <vector>

class Mutator{
public:
	Mutator(double mutaRate); 

	virtual void mutate(std::vector<int>& playArray) = 0;

protected: 
	double m_mutationRate; 
};

#endif