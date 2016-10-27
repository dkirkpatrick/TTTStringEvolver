/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#include "PointMutator.h"
#include "Random.h"
PointMutator::PointMutator(double mutaRate, double maxSize) : Mutator(mutaRate), m_maxAdd(maxSize) {};

Strategy PointMutator::mutate(Strategy p)
{
	Strategy ret(p);

	int addLoc = Random::getIndex(p.PlayArray.size());
	for (int i = 0; i < p.PlayArray.size(); i++) {
		if (Random::P(m_mutationRate)) {
			ret.PlayArray[i] = Random::getInt(0, 8);
		} else {
			ret.PlayArray[i] = p.PlayArray[i];
		}
	}
	return ret;
};