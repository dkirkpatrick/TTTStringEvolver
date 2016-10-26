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
	}; 

	std::vector<int> getMask(int i) {
		return myMasks[i]; 
	};
	
	std::map<int, std::vector<int>> dict() {
		return transformationDictionary;
	};

private: 
	void initDictionary(); 
	void initMasks(); 
	std::vector<std::vector<int>> myMasks;
	std::map<int, std::vector<int>> transformationDictionary; 
};

#endif

