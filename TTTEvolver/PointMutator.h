/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#ifndef PointMutator_H_
#define PointMutator_H_

#include "Mutator.h"

class PointMutator : public Mutator {
public:
	PointMutator(double mutaRate, int maxSize);
	void mutate(std::vector<int>& playArray);
private:
	int m_maxAdd;
};

#endif