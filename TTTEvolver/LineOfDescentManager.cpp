/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#include "LineOfDescentManager.h"
#include <set>
#include <queue>
#include <algorithm>
#include <iostream>

void LineOfDescent::setup(std::vector<Strategy> firstGen){
	for (Strategy p : firstGen){
		std::shared_ptr<LineOfDescentNode> tempptr (new LineOfDescentNode);
		tempptr->m_Strategy = p; 
		tempptr->parent = std::shared_ptr<LineOfDescentNode>(nullptr); 
		m_currentGen.push_back(tempptr); 
	}
}

void LineOfDescent::addGen(std::vector<Strategy> newGen){
	std::vector <std::shared_ptr<LineOfDescentNode>> newGenPtrs;
	for (Strategy p : newGen){
		std::shared_ptr<LineOfDescentNode> tempptr (new LineOfDescentNode);
		tempptr->m_Strategy = p;
		
		for (std::shared_ptr<LineOfDescentNode> LODptr : m_currentGen){
			if (LODptr->m_Strategy.generationID = p.parentID){
				tempptr->parent = LODptr; 
			}
		}

		newGenPtrs.push_back(tempptr); 
	}

	m_currentGen = newGenPtrs; 
}

std::string LineOfDescent::printLineOfDescent(){
	std::vector<Strategy> outputVector; 
	std::set<std::string> StrategysSeen;
	std::queue<std::shared_ptr<LineOfDescentNode>> processingQueue; 
	std::string outputString = ""; 

	for (std::shared_ptr<LineOfDescentNode> LODptr : m_currentGen){
		processingQueue.push(LODptr); 
	}

	std::cout << "After for" << std::endl; 

	while (!processingQueue.empty()){
		std::shared_ptr<LineOfDescentNode> temp = processingQueue.front(); 
		std::string tempID = temp->m_Strategy.getIDString(); 
		if (StrategysSeen.count(tempID) == 0){
			outputVector.push_back(temp->m_Strategy); 
			if (temp->parent.use_count() > 0){
				processingQueue.push(temp->parent); 
			}
			StrategysSeen.insert(tempID); 
		}
		processingQueue.pop(); 
	}

	std::cout << "After while" << std::endl;

	std::reverse(outputVector.begin(), outputVector.end()); 

	for (std::vector<Strategy>::iterator it = outputVector.begin(); it != outputVector.end(); it++)
	{
		outputString += it->toString();
	}

	return outputString; 
}
