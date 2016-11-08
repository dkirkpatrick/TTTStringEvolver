/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#ifndef ValidPointMutator_H_
#define ValidPointMutator_H_

#include "Mutator.h"
#include "BoardDictionary.h"

class ValidPointMutator : public Mutator {
public:
	ValidPointMutator(double mutaRate, int maxSize);
	Strategy mutate(Strategy temp);
private:
	int m_maxAdd;
	BoardDictionary myRef;
};

#endif