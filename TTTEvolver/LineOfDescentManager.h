#ifndef LineOfDescentManager_H_
#define LineOfDescentManager_H_

#include <vector>
#include "StructHeader.h"

class LineOfDescent {
public: 
	void setup(std::vector<Portfolio> firstGen); 
	void addGen(std::vector<Portfolio> newGen); 
	std::string printLineOfDescent(); 
private: 
	std::vector<std::shared_ptr<LineOfDescentNode>> m_currentGen; 
};

#endif