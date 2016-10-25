#include "PointMutator.h"
#include "Random.h"
PointMutator::PointMutator(double mutaRate, double maxSize) : Mutator(mutaRate), m_maxAdd(maxSize) {};

Strategy PointMutator::mutate(Strategy p)
{
	//Generates a location to add the random value to 
	int addLoc = Random::getIndex(p.PlayArray.size());

	//Copies the Strategy to be mutated 
	Strategy ret(p);

	//Add the random value at the random location 
	ret.PlayArray[addLoc] = Random::getIndex(10);

	return ret;
};