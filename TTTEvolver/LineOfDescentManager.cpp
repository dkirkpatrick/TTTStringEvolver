#include "LineOfDescentManager.h"
#include <set>
#include <queue>
#include <algorithm>
#include <iostream>

void LineOfDescent::setup(std::vector<Portfolio> firstGen){
	for (Portfolio p : firstGen){
		std::shared_ptr<LineOfDescentNode> tempptr (new LineOfDescentNode);
		tempptr->m_portfolio = p; 
		tempptr->parent = std::shared_ptr<LineOfDescentNode>(nullptr); 
		m_currentGen.push_back(tempptr); 
	}
}

void LineOfDescent::addGen(std::vector<Portfolio> newGen){
	std::vector <std::shared_ptr<LineOfDescentNode>> newGenPtrs;
	for (Portfolio p : newGen){
		std::shared_ptr<LineOfDescentNode> tempptr (new LineOfDescentNode);
		tempptr->m_portfolio = p;
		
		for (std::shared_ptr<LineOfDescentNode> LODptr : m_currentGen){
			if (LODptr->m_portfolio.generationID = p.parentID){
				tempptr->parent = LODptr; 
			}
		}

		newGenPtrs.push_back(tempptr); 
	}

	m_currentGen = newGenPtrs; 
}

std::string LineOfDescent::printLineOfDescent(){
	std::vector<Portfolio> outputVector; 
	std::set<std::string> portfoliosSeen;
	std::queue<std::shared_ptr<LineOfDescentNode>> processingQueue; 
	std::string outputString = ""; 

	for (std::shared_ptr<LineOfDescentNode> LODptr : m_currentGen){
		processingQueue.push(LODptr); 
	}

	std::cout << "After for" << std::endl; 

	while (!processingQueue.empty()){
		std::shared_ptr<LineOfDescentNode> temp = processingQueue.front(); 
		std::string tempID = temp->m_portfolio.getIDString(); 
		if (portfoliosSeen.count(tempID) == 0){
			outputVector.push_back(temp->m_portfolio); 
			if (temp->parent.use_count() > 0){
				processingQueue.push(temp->parent); 
			}
			portfoliosSeen.insert(tempID); 
		}
		processingQueue.pop(); 
	}

	std::cout << "After while" << std::endl;

	std::reverse(outputVector.begin(), outputVector.end()); 

	for (std::vector<Portfolio>::iterator it = outputVector.begin(); it != outputVector.end(); it++)
	{
		outputString += it->toString();
	}

	return outputString; 
}
