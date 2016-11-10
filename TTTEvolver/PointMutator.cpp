/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#include "PointMutator.h"
#include "Random.h"
PointMutator::PointMutator(double mutaRate, int maxSize) : Mutator(mutaRate), m_maxAdd(maxSize) {};

void PointMutator::mutate(std::vector<int>& playArray)
{
	for (int i = 0; i < playArray.size(); i++) {
		if (Random::P(m_mutationRate)) {
			playArray[i] = Random::getInt(0, 8);
		}
	}
};