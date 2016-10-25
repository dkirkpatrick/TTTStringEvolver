#include "Mutator.h"

Mutator::Mutator(double mutaRate) : m_mutationRate(mutaRate){}; 

std::vector<Portfolio> Mutator::mutate_all(std::vector<Portfolio> mGeneration){
	std::vector<Portfolio> temp;
	for (Portfolio mPort : mGeneration){
		if (rand() / RAND_MAX < m_mutationRate){
			temp.push_back(mutate(mPort));
		}
		else{
			temp.push_back(mPort); 
		}
	}
	return temp;
}