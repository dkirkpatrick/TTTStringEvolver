/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#include "StructHeader.h" 
#include <string>

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

std::string Strategy::toString(){
	std::string outputString = getIDString(); 

	outputString += "-"; 
	outputString += std::to_string(parentID); 

	outputString += " [ ";
	for (size_t i = 0; i < PlayArray.size() - 1; i++){
		outputString += std::to_string(PlayArray.at(i));
		outputString += ", "; 
	}

	outputString += std::to_string(PlayArray.at(PlayArray.size() - 1));
	outputString += " ]\n";

	return outputString; 
}