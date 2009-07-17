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
	Radian angle;
	Radian angleUp;
	Vector3 cuePosition;
	ApplicationObject *ball;
	ApplicationObject *balls[9];
	bool visible[9];
	ApplicationObject *cueNode;
	SceneNode* targetNode;
	SceneNode* lineNode;
	int c;
	Vector3 lastPosition;
	Real timeSinceLastFrame;


	bool ballsStoped();
	void adjustBallVelocities();
	void handleBallDropping();
	void handleAiming();
	void handleCue();
	void handleStriking();

public:
	BilliardCollisionListener(RenderWindow* win, CollideCamera* cam,World* world,
		ApplicationObject *ball,ApplicationObject *balls[9],ApplicationObject *cueNode,SceneManager* sceneManager);

	bool frameStarted(const FrameEvent& evt)
	{
		timeSinceLastFrame=evt.timeSinceLastFrame;
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

		//if (mKeyboard->isKeyDown(OIS::KC_T))
		//{
		//	OgreRefApp::Box *b=mWorld->createBox("testbox",20,20,20,Vector3(0,15,0));
		//	b->getEntity()->setMaterialName("Billiards/Wood");

		//}
		
		return true;
	}
};

#endif