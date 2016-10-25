#ifndef RandomAddMutator_H_
#define RandomAddMutator_H_

#include "Mutator.h"

class RandomAddMutator : public Mutator {
public: 
	RandomAddMutator(double mutaRate, double maxSize); 
	Portfolio mutate(Portfolio temp); 
private: 
	double m_maxAdd; 
};

#endif