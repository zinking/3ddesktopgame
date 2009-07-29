#include "GameRuleManager.h"

GameRuleManager *GameRuleManager::mgr;

GameRuleManager::GameRuleManager() : turn(PLAYER1), comboCount(0)
{
	for (int i = 0; i != BALL_NUM; ++i) {
		balls[i] = true;
	}
	scores[0] = scores[1] = 0;
}

void GameRuleManager::changePlayerTurn()
{
	comboCount = 0;
	turn = (turn == PLAYER1 ? PLAYER2 : PLAYER1);
}

Player GameRuleManager::getCurrentTurn()
{
	return turn;
}

Player GameRuleManager::getOpponent()
{
	return (turn == PLAYER1 ? PLAYER2 : PLAYER1);
}

int GameRuleManager::getScore(Player player)
{
	return scores[player];
}

void GameRuleManager::potABall(int ballNum)
{
	//hasCommittedFouls |= !(doPotABall(ballNum));

	assert(ballNum >= 0 && ballNum < BALL_NUM);

	if (ballNum == 0) { //return false;
		foulsCommitted.push_back(new CueBallPottedFoul());
		return;
	}

	assert(balls[ballNum]);

	//hasPottedBalls = true;
	this->balls[ballNum] = false;
	ballsPotted.push_back(ballNum);
	//return true;
}

//bool GameRuleManager::doPotABall(int ballNum)
//{
//	assert(ballNum >= 0 && ballNum < BALL_NUM);
//
//	if (ballNum == 0) return false;
//
//	assert(balls[ballNum]);
//
//	hasPottedBalls = true;
//	this->balls[ballNum] = false;
//	ballsPotted.push_back(ballNum);
//	return true;
//}

void GameRuleManager::startHit(int ballNum)
{
	//hasCommittedFouls |= (ballNum != 0);
	if (ballNum != 0) {
		foulsCommitted.push_back(new CueBallNotHitFoul());
		//hasCommittedFouls = true;
		return;
	}
	foulsCommitted.push_back(new TargetBallNotHitFoul(0));
}

void GameRuleManager::hitFirstBall(int ballNum)
{
	//hasCommittedFouls |= (nextToHit() != ballNum);
	delete (*foulsCommitted.rbegin());
	foulsCommitted.pop_back();
	if (nextToHit() != ballNum) {
		foulsCommitted.push_back(new TargetBallNotHitFoul(ballNum));
	}
}

int GameRuleManager::nextToHit()
{
	for (int i = 1; i != BALL_NUM; ++i)
		if (balls[i]) 
			return i;
	return -1;
}

HittingState GameRuleManager::endHit()
{
	//bool /* hcf = hasCommittedFouls, */ hpb = hasPottedBalls;
	//hasCommittedFouls = false;
	//hasPottedBalls = false;

	/*if (!balls[9]) {
		if (!hcf) {
			return GAME_OVER;
		} else {
			balls[9] = true;
		}
	}*/

	/*if (hcf || !hpb) {
		comboCount = 0;
		changePlayerTurn();
		return CHANGE_PLAYER;
	}

	return (++comboCount == 1 ? GO_ON : COMBO);*/

	//bool noFoul = foulsCommitted.empty(), hpb = !ballsPotted.empty();

	HittingState returnState;

	if (foulsCommitted.empty() && !ballsPotted.empty()) {
		int awards = 0;
		for (vector<int>::const_iterator i = ballsPotted.begin(); 
			i != ballsPotted.end(); ++i) {
			awards += (*i);
		}
		awards += (++comboCount > 1 ? pow(2, (float) (comboCount - 1)) : 0);
		scores[turn] += awards;

		ballsPotted.clear();
		//return comboCount == 1 ? GO_ON : COMBO;
		returnState = (comboCount == 1 ? GO_ON : COMBO);
	}
	else {
		int awards = 0;
		for (vector<Foul*>::const_iterator i = foulsCommitted.begin(); 
			i != foulsCommitted.end(); ++i) {
			awards = max(awards, (*i)->scoreAwardedToOpponent());
		}
		scores[getOpponent()] += awards;

		this->ballsPotted.clear();	
		this->clearFouls();
		this->changePlayerTurn();
		//return CHANGE_PLAYER;
		returnState = CHANGE_PLAYER;
	}

	return this->isGameOver() ? GAME_OVER : returnState;
	
}

bool GameRuleManager::isGameOver()
{
	return nextToHit() == -1;
}

void GameRuleManager::startNewGame(Player playerToBreak /* = PLAYER1 */)
{
	turn = playerToBreak; 
	//hasCommittedFouls = false;
	//hasPottedBalls = false;
	comboCount = 0;
	for (int i = 0; i != BALL_NUM; ++i) {
		balls[i] = true;
	}
	scores[0] = scores[1] = 0;
}

void GameRuleManager::clearFouls()
{
	for (vector<Foul*>::iterator i = foulsCommitted.begin(); 
		i != foulsCommitted.end(); ++i) {
		delete (*i);
	}
	foulsCommitted.clear();
}
