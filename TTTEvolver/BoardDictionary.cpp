/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#include "BoardDictionary.h"
#include "TTTEngine.h"
#include <iostream>
#include <map>

void BoardDictionary::initMasks() {
	myMasks = std::vector<std::vector<int>>();
	std::vector<int> mask0 = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	std::vector<int> mask1 = { 0, 3, 6, 1, 4, 7, 2, 5, 8 };
	std::vector<int> mask2 = { 2, 1, 0, 5, 4, 3, 8, 7, 6 };
	std::vector<int> mask3 = { 2, 5, 8, 1, 4, 7, 0, 3, 6 };
	std::vector<int> mask4 = { 6, 3, 0, 7, 4, 1, 8, 5, 2 };
	std::vector<int> mask5 = { 6, 7, 8, 3, 4, 5, 0, 1, 2 };
	std::vector<int> mask6 = { 8, 5, 2, 7, 4, 1, 6, 3, 0 };
	std::vector<int> mask7 = { 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	myMasks.push_back(mask0);
	myMasks.push_back(mask1);
	myMasks.push_back(mask2);
	myMasks.push_back(mask3);
	myMasks.push_back(mask4);
	myMasks.push_back(mask5);
	myMasks.push_back(mask6);
	myMasks.push_back(mask7);
}


void BoardDictionary::initPlays() {
	TTTGame temp(3);
	validPlays = std::map<int, std::vector<int>>();
	for (auto member : transformationDictionary) {
		validPlays[member.second.at(2)] = temp.getValidPlaysFromBase3(member.second.at(0));
	}
}

void BoardDictionary::initDictionary() {
	std::vector<int> temp = {};
	initDictionary(temp);
}

void BoardDictionary::initDictionary(std::vector<int> whichMasks) {
	TTTGame temp(3);
	int outercount = 0;
	std::map<int, int> boardsSeen = std::map<int, int>();
	transformationDictionary = std::map<int, std::vector<int>>();
	std::vector<int> myTempVector = std::vector<int>();
	for (int i : validBoards) {
		//MAP IS: 
		//BOARD --> TRANSFORMEDBOARD, WHICHMASK, POSITIONINARRAY
		std::pair<int, int> p;
		if (whichMasks.empty()) {
			p = temp.getMinimumBoardAndPermutationFromBase3(i);
		}
		else {
			p = temp.getMinimumBoardAndPermutationFromBase3UsingSubset(i, whichMasks);
		}

		if (boardsSeen.count(p.first) <= 0) {
			boardsSeen.emplace(p.first, outercount);
			outercount++;
		}
		myTempVector.push_back(p.first); myTempVector.push_back(p.second); myTempVector.push_back(boardsSeen.at(p.first));
		transformationDictionary[i] = myTempVector;
		myTempVector.clear();
	}
	reducedSize = outercount;
}

