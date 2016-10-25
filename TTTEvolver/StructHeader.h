#ifndef StructHeader_H_
#define StructHeader_H_

#include <vector>
#include <cmath>
#include <memory>

struct Portfolio{ 
	std::vector<double> ValueArray;
	int generationID; 
	int parentID; 
	int generation; 
	double fitness;
	void normalize(); 
	friend bool operator<(const Portfolio& l, const Portfolio& r); 
	std::string toString(); 
	std::string getIDString(); 
}; 

struct LineOfDescentNode{
	std::shared_ptr<LineOfDescentNode> parent;
	Portfolio m_portfolio; 
};

#endif // !StructHeader_H_
