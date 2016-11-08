/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#include "ValidPointMutator.h"
#include "Random.h"


ValidPointMutator::ValidPointMutator(double mutaRate, double maxSize) : Mutator(mutaRate), m_maxAdd(maxSize) {
	myRef = BoardDictionary();
};

Strategy ValidPointMutator::mutate(Strategy p)
{
	Strategy ret(p);
	std::vector<int> temp;
	int addLoc = Random::getIndex(p.PlayArray.size());
	for (int i = 0; i < p.PlayArray.size(); i++) {
		if (Random::P(m_mutationRate)) {
			temp = myRef.plays().at(i % (p.PlayArray.size() / 2));
			if (temp.size() > 0) {
				ret.PlayArray[i] = temp.at(Random::getIndex(temp.size())); 
			} else {
				ret.PlayArray[i] = 0;
			}
		}
		else {
			ret.PlayArray[i] = p.PlayArray[i];
		}
	}
	return ret;
};