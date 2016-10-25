#include "StructHeader.h" 
#include <string>

bool operator<(const Portfolio& l, const Portfolio& r)
{
	return l.fitness < r.fitness;
}

void Portfolio::normalize(){
	double dist = 0.0; 
	for (double d : ValueArray){
		dist += pow(d,2); 
	}
	double length = sqrt(dist); 
	for (int i = 0; i < ValueArray.size(); i++){
		ValueArray[i] = (ValueArray[i] * sqrt(ValueArray.size()) / length); 
	}
}

std::string Portfolio::getIDString(){
	std::string outputString = "";

	outputString += std::to_string(generation);
	outputString += "-";
	outputString += std::to_string(generationID);

	return outputString;
}

std::string Portfolio::toString(){
	std::string outputString = getIDString(); 

	outputString += "-"; 
	outputString += std::to_string(parentID); 

	outputString += " [ ";
	for (int i = 0; i < ValueArray.size() - 1; i++){
		outputString += std::to_string(ValueArray.at(i));
		outputString += ", "; 
	}

	outputString += std::to_string(ValueArray.at(ValueArray.size() - 1));
	outputString += " ]\n";

	return outputString; 
}