/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright 2016, all rights reserved
*/

#include "Mutator.h"

Mutator::Mutator(double mutaRate) : m_mutationRate(mutaRate){}; 

std::vector<Strategy> Mutator::mutate_all(std::vector<Strategy> mGeneration){
	std::vector<Strategy> temp;
	for (Strategy mPort : mGeneration){
		if (rand() / RAND_MAX < m_mutationRate){
			temp.push_back(mutate(mPort));
		}
		else{
			temp.push_back(mPort); 
		}
	}
	return temp;
}