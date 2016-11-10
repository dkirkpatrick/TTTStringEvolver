/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#include "StructHeader.h" 

#include "Random.h"
#include <string>
#include <iostream>

bool operator<(const Strategy& l, const Strategy& r)
{
	return l.fitness < r.fitness;
}

std::string Strategy::getIDString(){
	std::string outputString = "";

	outputString += std::to_string(generation);
	outputString += "-";
	outputString += std::to_string(generationID);

	return outputString;
}

Strategy::Strategy(std::string initializationType, int genIDctr, int m_sizeStrategy, BoardDictionary& myRef, Mutator* mMutator)
{
	m_mutator = mMutator;
	fitness = 0.0;
	generation = 0;
	generationID = genIDctr;
	win = 0;
	loss = 0;
	draw = 0;
	winPop = 0;
	lossPop = 0;
	drawPop = 0;
	winRand = 0;
	lossRand = 0;
	drawRand = 0;
	winPerf = 0;
	lossPerf = 0;
	drawPerf = 0;
	ancestor = std::shared_ptr<Strategy>(nullptr);

	if (initializationType == "uniform") {
		for (size_t i = 0; i < m_sizeStrategy; i++) {
			PlayArray.push_back(1);
		}
	}
	else if (initializationType == "random") {
		for (size_t i = 0; i < m_sizeStrategy; i++) {
			PlayArray.push_back(Random::getInt(0, 8));
		}
	}
	else if (initializationType == "validRand") {
		std::vector<int> temp;
		for (size_t i = 0; i < m_sizeStrategy; i++) {
			temp = myRef.plays().at(i % (m_sizeStrategy / 2));
			if (temp.size() > 0) {
				PlayArray.push_back(temp.at(Random::getIndex(temp.size())));
			}
			else {
				PlayArray.push_back(0);
			}
		}
	}
	else {
		std::cout << "ERROR: NO POPULATION INITIALIZATION ASSIGNED" << std::endl;
	}

}

Strategy::Strategy(std::shared_ptr<Strategy> sPtr, int genIDctr)
{
	m_mutator = sPtr->m_mutator; 
	fitness = 0.0;
	generationID = genIDctr;
	win = 0;
	loss = 0;
	draw = 0;
	winPop = 0;
	lossPop = 0;
	drawPop = 0;
	winRand = 0;
	lossRand = 0;
	drawRand = 0;
	winPerf = 0;
	lossPerf = 0;
	drawPerf = 0;
	ancestor = sPtr;
	for (std::vector<int>::iterator it = sPtr->PlayArray.begin(); it != sPtr->PlayArray.end(); it++)
	{
		PlayArray.push_back(*it);
	}
	m_mutator->mutate(PlayArray); 
	generation = sPtr->generation + 1;
}

std::string Strategy::toString(){
	std::string outputString = getIDString(); 

	outputString += " [ ";
	for (size_t i = 0; i < PlayArray.size() - 1; i++){
		outputString += std::to_string(PlayArray.at(i));
		outputString += ", "; 
	}

	outputString += std::to_string(PlayArray.at(PlayArray.size() - 1));
	outputString += " ]\n";

	return outputString; 
}

std::string Strategy::toStringLOD() {
	std::string outputString = getIDString();

	outputString += ", ";
	outputString += std::to_string(win);
	outputString += ", ";
	outputString += std::to_string(loss);
	outputString += ", ";
	outputString += std::to_string(draw);
	outputString += ", ";
	outputString += std::to_string(winPop);
	outputString += ", ";
	outputString += std::to_string(lossPop);
	outputString += ", ";
	outputString += std::to_string(drawPop);
	outputString += ", ";
	outputString += std::to_string(winRand);
	outputString += ", ";
	outputString += std::to_string(lossRand);
	outputString += ", ";
	outputString += std::to_string(drawRand);
	outputString += ", ";
	outputString += std::to_string(winPerf);
	outputString += ", ";
	outputString += std::to_string(lossPerf);
	outputString += ", ";
	outputString += std::to_string(drawPerf);
	outputString += "\n";

/*	outputString += ", [ ";
	for (size_t i = 0; i < PlayArray.size() - 1; i++) {
		outputString += std::to_string(PlayArray.at(i));
		outputString += ", ";
	}

	outputString += std::to_string(PlayArray.at(PlayArray.size() - 1));
	outputString += " ]\n";
	*/
	return outputString;
}