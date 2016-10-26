/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#ifndef PointMutator_H_
#define PointMutator_H_

#include "Mutator.h"

class PointMutator : public Mutator {
public:
	PointMutator(double mutaRate, double maxSize);
	Strategy mutate(Strategy temp);
private:
	double m_maxAdd;
};

#endif