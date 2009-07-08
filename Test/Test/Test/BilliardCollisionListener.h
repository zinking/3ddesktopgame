#ifndef BILLIARDCOLLISIONLISTENER_H
#define BILLIARDCOLLISIONLISTENER_H

#include <Windows.h>
#include "OgreReferenceAppLayer.h"
#include "MyFrameListener.h"
#include "ExampleRefAppApplication.h"
#include "OgreStringConverter.h"

//RaySceneQuery* rsq = 0;

// Event handler to add ability to alter curvature
class BilliardCollisionListener : public MyFrameListener
{
private:
	World* mWorld;
	bool toBall;
	bool stroken;
	bool cueVisible;
	bool white;
	Real dis;
	Real angle;
	Vector3 cuePosition;
	ApplicationObject *ball;
	ApplicationObject *balls[9];
	bool visible[9];
	SceneNode* cueNode;
	SceneNode* targetNode;
	SceneNode* lineNode;
	int c;

	bool ballsStoped();
	void adjustBallVelocities();
	void handleBallDropping();
	void handleAiming();
	void handleCue();
	void handleStriking();

public:
	BilliardCollisionListener(RenderWindow* win, CollideCamera* cam,World* world,
		ApplicationObject *ball,ApplicationObject *balls[9],SceneManager* sceneManager);

	bool frameStarted(const FrameEvent& evt)
	{
		adjustBallVelocities();
		handleBallDropping();
		handleAiming();
		handleCue();
		handleStriking();
		if((ball->getPosition()-balls[0]->getPosition()).length()<=8&&!ballsStoped())
		{
			c++;
			mDebugText=StringConverter::toString(c);
			//PlaySound(TEXT ("215.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}

		
		
		return true;
	}
};

#endif