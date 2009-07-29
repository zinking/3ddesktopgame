#ifndef BILLIARDCOLLISIONLISTENER_H
#define BILLIARDCOLLISIONLISTENER_H

#include <Windows.h>
#include "OgreReferenceAppLayer.h"
#include "MyFrameListener.h"
#include "ExampleRefAppApplication.h"
#include "OgreStringConverter.h"
#include "RigidBody.h"
#include "Obstacle.h"
#include "AudioManager.h"
#include "GameRuleManager.h"
#include "ogre2d-main.h"
#include "TextRenderer.h"
#include "stdafx.h"

// Event handler to add ability to alter curvature
class BilliardCollisionListener : public MyFrameListener
{
private:
	World* mWorld;
	CollideCamera* camera;

	ApplicationObject *ball;
	bool whiteBallDropped;

	ApplicationObject *balls[9];
	//bool visible[9];

	//Obstacle *obstacle[2];
	ApplicationObject *obstacle;
	ApplicationObject *cussions[6];
	Radian obstacleAngle;
	RigidBody *bodies[2];
	SceneNode *cueNode;

	Radian angle;
	Radian angleUp;
	
	Vector3 lastPosition;
	float lastD[10];
	Radian lastAngle;

	Ogre2dManager* ogre2dManager;

	Real timeSinceLastFrame;
	
	float camAngle;
	float camTrans;

	bool startGame;
	bool isBallHit;
	bool firstHit;
	bool hitEnded;
	bool pocketSoundPlayed[10];

	int c;

	bool whiteBallPosInUse(Vector3 pos);
	void resetWhiteBall();
	void resetBalls();
	bool ballsStopped();
	void handlePlayer();
	void handleBallVelocities();
	void handleBallCollision();
	void handleBallDropping();
	void handleCue();
	void handleObstacle();
	void handleCamera();

public:
	BilliardCollisionListener(RenderWindow* win, CollideCamera* cam,World* world,RigidBody *bodies[2]);

	bool frameStarted(const FrameEvent& evt)
	{
		timeSinceLastFrame=evt.timeSinceLastFrame;
		handlePlayer();
		handleBallVelocities();
		handleBallDropping();
		handleCue();
		handleBallCollision();
		
		return true;
	}
};

#endif