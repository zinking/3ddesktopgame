#ifndef BILLIARDCOLLISIONLISTENER_H
#define BILLIARDCOLLISIONLISTENER_H

#include <Windows.h>
#include "OgreReferenceAppLayer.h"
#include "MyFrameListener.h"
#include "ExampleRefAppApplication.h"
#include "OgreStringConverter.h"
#include "RigidBody.h"
#include "Obstacle.h"
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
	bool visible[9];

	//Obstacle *obstacle[2];
	ApplicationObject *obstacle;
	Radian obstacleAngle;
	RigidBody *bodies[2];
	SceneNode *cueNode;

	Radian angle;
	Radian angleUp;
	
	Vector3 lastPosition;
	float lastD[10];
	Radian lastAngle;

	Real timeSinceLastFrame;
	
	float camAngle;
	float camTrans;


	bool ballsStopped();
	void adjustBallVelocities();
	void handleBallDropping();
	void handleCue();
	void handleObstacle();
	void handleCamera();

public:
	BilliardCollisionListener(RenderWindow* win, CollideCamera* cam,World* world,
		ApplicationObject *ball,ApplicationObject *balls[9],RigidBody *bodies[2],
		ApplicationObject *obstacle,SceneNode *cueNode);

	bool frameStarted(const FrameEvent& evt)
	{
		timeSinceLastFrame=evt.timeSinceLastFrame;
		adjustBallVelocities();
		handleBallDropping();
		handleCue();
		//if((ball->getPosition()-balls[0]->getPosition()).length()<=8&&!ballsStoped())
		//{
		//	c++;
		//	mDebugText=StringConverter::toString(c);
		//	//PlaySound(TEXT ("215.wav"), NULL, SND_FILENAME | SND_ASYNC);
		//}
		return true;
	}
};

#endif