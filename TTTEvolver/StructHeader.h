/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#ifndef StructHeader_H_
#define StructHeader_H_

#include <vector>
#include <cmath>
#include <memory>
#include "Mutator.h"
#include "BoardDictionary.h"

struct Strategy{ 
	Strategy(std::string initializationType, int genIDctr, int m_sizeStrategy, BoardDictionary& myRef, Mutator* mMutator);
	Strategy(std::shared_ptr<Strategy> sPtr, int genIDctr); 
	std::vector<int> PlayArray;
	int generationID; 
	int generation; 
	double fitness;
	friend bool operator<(const Strategy& l, const Strategy& r); 
	std::string toString(); 
	std::string toStringLOD();
	std::string getIDString(); 
	int win; 
	int loss; 
	int draw;  
	int winPop;
	int lossPop;
	int drawPop;
	int winRand;
	int lossRand;
	int drawRand;
	int winPerf;
	int lossPerf;
	int drawPerf;
	std::shared_ptr<Strategy> ancestor; 
	Mutator* m_mutator; 
}; 

#endif // !StructHeader_H_
