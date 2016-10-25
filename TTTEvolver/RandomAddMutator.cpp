#include "RandomAddMutator.h"

RandomAddMutator::RandomAddMutator(double mutaRate, double maxSize) : Mutator(mutaRate), m_maxAdd(maxSize){}; 

Portfolio RandomAddMutator::mutate(Portfolio p)
{
	//Creates a random value between 0 and max_add to add to one value in the portfolio 
	double addVal = ((double) rand() / (double) RAND_MAX) * m_maxAdd; 

	//Generates a location to add the random value to 
	int addLoc = rand() % p.ValueArray.size();
	
	//Copies the portfolio to be mutated 
	Portfolio ret(p); 

	//Add the random value at the random location 
	ret.ValueArray[addLoc] += addVal; 

	//Normalize the vector being returned 
	ret.normalize();  

	return ret;
}; 