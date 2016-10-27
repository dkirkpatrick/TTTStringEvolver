/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#include "Mutator.h"
#include "Random.h"
Mutator::Mutator(double mutaRate) : m_mutationRate(mutaRate){}; 

std::vector<Strategy> Mutator::mutate_all(std::vector<Strategy> mGeneration){
	std::vector<Strategy> temp;
	for (Strategy mPort : mGeneration){
		temp.push_back(mutate(mPort));
	}
	return temp;
}