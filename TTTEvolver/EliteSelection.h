#ifndef EliteSelection_H_
#define EliteSelection_H_

#include "Selector.h"
#include "TTTEngine.h"
#include "BoardDictionary.h"
class EliteSelector : public Selector{
public:
	EliteSelector(double rateSel, int numEval);
	EliteSelector(double rateSel, int numEval, double winVal, double lossVal, double drawVal);
	std::vector<Strategy> createNextGen(std::vector<Strategy> oldGeneration); 

	double play(Strategy s1, Strategy s2); 
	int getPlay(Strategy s, TTTGame mGame, int whichPlayer);

private:
	BoardDictionary myRef; 
	double m_winVal; 
	double m_lossVal; 
	double m_drawVal; 
};


#endif