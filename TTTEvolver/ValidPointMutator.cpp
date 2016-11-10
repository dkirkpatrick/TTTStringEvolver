/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#include "ValidPointMutator.h"
#include "Random.h"


ValidPointMutator::ValidPointMutator(double mutaRate, int maxSize) : Mutator(mutaRate), m_maxAdd(maxSize) {
	myRef = BoardDictionary();
};

void ValidPointMutator::mutate(std::vector<int>& playArray)
{
	std::vector<int> temp;
	for (int i = 0; i < playArray.size(); i++) {
		if (Random::P(m_mutationRate)) {
			temp = myRef.plays().at(i % (playArray.size() / 2));
			if (temp.size() > 0) {
				playArray[i] = temp.at(Random::getIndex(temp.size()));
			} else {
				playArray[i] = 0;
			}
		}
	}
};