#pragma once

#include "stdafx.h"

#define BALL_NUM   10

enum Player { PLAYER1, PLAYER2 };
enum HittingState { GO_ON, COMBO, CHANGE_PLAYER, GAME_OVER };

class Foul {
public:
	virtual int scoreAwardedToOpponent() const = 0;
};

class CueBallNotHitFoul : public Foul {
public:
	int scoreAwardedToOpponent() const { return 4; }
};

class TargetBallNotHitFoul : public Foul {
public:
	TargetBallNotHitFoul(int ballNum) : ball(ballNum) {}

	int scoreAwardedToOpponent() const {
		return ball > 4 ? ball : 4;
	}
private:
	int ball;
};

class CueBallPottedFoul : public Foul {
public:
	int scoreAwardedToOpponent() const { return 4; }
};

class GameRuleManager
{
public:
	static GameRuleManager* getSingleton()
	{
		if (mgr == 0)
			mgr = new GameRuleManager();
		return mgr;
	}
	
protected:
	GameRuleManager();
	//	: turn(PLAYER1), 
	//					//hasCommittedFouls(false), 
	//					//hasPottedBalls(false), 
	//					comboCount(0)
	//{
	//	for (int i = 0; i != BALL_NUM; ++i) {
	//		balls[i] = true;
	//	}
	//	scores[0] = scores[1] = 0;
	//}
	
	virtual ~GameRuleManager()
	{}

	static GameRuleManager *mgr;

private:
	Player turn;
	bool balls[BALL_NUM];
	//bool hasCommittedFouls;
	//bool hasPottedBalls;
	int comboCount;

	int scores[2];
	vector<int> ballsPotted;
	vector<Foul*> foulsCommitted;

public:
	Player getCurrentTurn();
	void potABall(int ballNum);
	void startHit(int ballNum);
	void hitFirstBall(int ballNum);
	HittingState endHit();
	void startNewGame(Player playerToBreak = PLAYER1);

	int getScore(Player player);

private:
	int nextToHit();
	//bool doPotABall(int ballNum);
	void changePlayerTurn();
	Player getOpponent();
	void clearFouls();
	bool isGameOver();

};


