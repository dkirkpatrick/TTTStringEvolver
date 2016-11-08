/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#include <map>
#include <vector>

#ifndef __BOARDDICTIONARY__
#define __BOARDDICTIONARY__


class BoardDictionary {
public: 
	BoardDictionary() {
		initDictionary(); 
		initMasks(); 
		initPlays(); 
	}; 

	std::vector<int> getMask(int i) {
		return myMasks[i]; 
	};
	
	const std::map<int, std::vector<int>>& dict() {
		return transformationDictionary;
	};

	const std::map<int, std::vector<int>>& plays() {
		return validPlays; 
	}

private: 
	void initDictionary(); 
	void initMasks();
	void initPlays(); 
	std::vector<std::vector<int>> myMasks;
	std::map<int, std::vector<int>> transformationDictionary; 
	std::map<int, std::vector<int>> validPlays; 
};

#endif

