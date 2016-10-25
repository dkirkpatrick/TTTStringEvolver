#include <map>
#include <vector>

#ifndef __BOARDDICTIONARY__
#define __BOARDDICTIONARY__


class BoardDictionary {
public: 
	BoardDictionary() {
		initDictionary(); 
	}; 
	
	std::map<int, std::pair<int, std::vector<int>>> dict() {
		return transformationDictionary;
	}
private: 
	void initDictionary(); 
	std::map<int, std::pair<int, std::vector<int>>> transformationDictionary; 
};

#endif

