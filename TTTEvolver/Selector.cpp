/*
*	Part of the TTTStringEvolver by Douglas Kirkpatrick
*	Copyright (c) 2016, all rights reserved
*/

#include "Selector.h"

Selector::Selector(double rateSel, int numEval, double winVal, double lossVal, double drawVal, bool strtAdvtg, int gamesVsRand) : 
	m_rateSelection(rateSel), m_numEval(numEval), m_winVal(winVal), m_lossVal(lossVal), m_drawVal(drawVal), m_startAdvantage(strtAdvtg), m_gamesVsRandom(gamesVsRand) {
	myRef = BoardDictionary();
	m_randomPlayer = new TTTRandomPlayer();
	m_perfectPlayer = new TTTMinimaxPlayer();
}

int Selector::play(std::shared_ptr<Strategy> s1, TTTPlayer* myPlayer, int startPlayer) {
	int playCount = 0;
	TTTGame myGame = TTTGame(3);

	if (m_startAdvantage) {
		myGame.play(4, 1);
	}

	// Assign player to brain, opponent
	int s1Plays = startPlayer;
	int TTTPlayerPlays = (s1Plays == 2 ? 1 : 2);
	bool whoPlays = (TTTPlayerPlays == 1);
	int i = 0;
	// Handles the result until a conclusion is reached 
	while (myGame.gameWon() == 0 && !myGame.gameDraw() && i < 18) {
		i++;
		if (whoPlays) {
			std::vector<int> otherPlay = myPlayer->getPlay(myGame, TTTPlayerPlays);
			myGame.play(otherPlay.at(0), otherPlay.at(1), TTTPlayerPlays);
			whoPlays = false;
		}
		else {
			int myPlay = getPlay(s1, myGame, s1Plays);
			myGame.play(myPlay, s1Plays);
			whoPlays = true;
		}
	}

	// Outputs based on game results 
	if (myGame.gameDraw()) {
		return 0;
	}
	else if (myGame.gameWon() == s1Plays) {
		return 1;
	}
	else {
		return -1;
	}
}

int Selector::play(std::shared_ptr<Strategy> s1, std::shared_ptr<Strategy> s2) {
	int playCount = 0;
	TTTGame myGame = TTTGame(3);

	if (m_startAdvantage) {
		myGame.play(4, 1);
	}

	// Assign player to brain, opponent
	int s1Plays = 1;
	int s2Plays = 2;
	bool whoPlays = false;
	int i = 0;
	// Handles the result until a conclusion is reached 
	while (myGame.gameWon() == 0 && !myGame.gameDraw() && i < 18) {
		i++;
		if (whoPlays) {
			int otherPlay = getPlay(s2, myGame, s2Plays);
			myGame.play(otherPlay, s2Plays);
			whoPlays = false;
		}
		else {
			int myPlay = getPlay(s1, myGame, s1Plays);
			myGame.play(myPlay, s1Plays);
			whoPlays = true;
		}
	}

	// Outputs based on game results 
	if (myGame.gameDraw()) {
		return 0;
	}
	else if (myGame.gameWon() == s1Plays) {
		return 1;
	}
	else {
		return -1;
	}
}

int Selector::getPlay(std::shared_ptr<Strategy> s, TTTGame& mGame, int whichPlayer) {
	std::vector<int> lookup = myRef.dict().at(mGame.base3Board());
	std::vector<int> permute = mGame.getInversePermutation(myRef.getMask(lookup.at(1)));
	int offset = (whichPlayer == 1) ? 0 : 1582;
	return permute.at(s->PlayArray.at(lookup.at(2) + offset));
}