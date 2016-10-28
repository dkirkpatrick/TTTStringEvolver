//
//  TTTPlayers.h
//
//  Created by Douglas Kirkpatrick on  3/30/16.
//  Copyright (c) 2016 Douglas Kirkpatrick. All rights reserved.
//

#ifndef __TTTMINIMAXPLAYER__
#define __TTTMINIMAXPLAYER__

#include <vector>
#include <map> 
#include "TTTEngine.h"

// Generic wrapper class for polymorphism
class TTTPlayer {
public:
	virtual std::vector<int> getPlay(TTTGame& myGame, int player) = 0;
};

// Player that choses a random position on the game board 
class TTTRandomPlayer : public TTTPlayer {
public:
	std::vector<int> getPlay(TTTGame& myGame, int player) override;
};

//Player that plays optimally on a 3x3 board using minimax-precomputed plays
class TTTMinimaxPlayer : public TTTPlayer {
public:
	TTTMinimaxPlayer();
	std::vector<int> getPlay(TTTGame& myGame, int player) override;

private:
	void loadPlayer1();
	void loadPlayer2();
	std::map<int, std::vector<int>> p1BestPlays;
	std::map<int, std::vector<int>> p2BestPlays;
};

//Player that plays optimally some subset of the time 
class TTTImperfectPlayer : public TTTPlayer {
public:
	TTTImperfectPlayer(double optimalPlayPercentage);
	std::vector<int> getPlay(TTTGame& myGame, int player) override;
private:
	double myOptimalPlayPercentage;
	TTTMinimaxPlayer myMMPlayer;
	TTTRandomPlayer myRandPlayer;
};

#endif