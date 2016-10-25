/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick 
*	Copyright 2016, all rights reserved
*/


#ifndef StructHeader_H_
#define StructHeader_H_

#include <vector>
#include <cmath>
#include <memory>

struct Strategy{ 
	std::vector<int> PlayArray;
	int generationID; 
	int parentID; 
	int generation; 
	double fitness;
	friend bool operator<(const Strategy& l, const Strategy& r); 
	std::string toString(); 
	std::string getIDString(); 
}; 

struct LineOfDescentNode{
	std::shared_ptr<LineOfDescentNode> parent;
	Strategy m_Strategy; 
};

#endif // !StructHeader_H_