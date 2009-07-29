

#include "BilliardCollisionListener.h"
#include "ObjectPosition.h"
#include "Obstacle.h"

BilliardCollisionListener::BilliardCollisionListener(RenderWindow* win, CollideCamera* cam,World* world,
							RigidBody *bodies[2]): MyFrameListener(win, cam)
{
	mWorld=world;
	ogre2dManager=new Ogre2dManager;
	Ogre::TextureManager::getSingleton().load("currentPlayer.png",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::TextureManager::getSingleton().load("playerWaiting.png",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	ogre2dManager->init(mWorld->getSceneManager(),Ogre::RENDER_QUEUE_OVERLAY,true);

	this->camera=cam;
	this->ball=mWorld->getApplicationObject("ball");
	for (int i=0;i<9;i++)
		this->balls[i]=mWorld->getApplicationObject("ball"+StringConverter::toString(i+1));
	for (int i=0;i<6;i++)
		this->cussions[i]=mWorld->getApplicationObject("cussion"+StringConverter::toString(i));
	for (int i=0;i<2;i++)
		this->bodies[i]=bodies[i];
	this->obstacle=mWorld->getApplicationObject("obstacle");
	this->cueNode=mWorld->getSceneManager()->getSceneNode("cueNode");

	whiteBallDropped=false;
	angle=0;
	angleUp=0;
	lastPosition=cueNode->getPosition();
	startGame=false;
	isBallHit=false;
	firstHit=false;
	for (int i=0;i<10;i++)
	{
		pocketSoundPlayed[i]=false;
	}
	GameRuleManager::getSingleton()->startNewGame();
	new TextRenderer();
	TextRenderer::getSingleton().addTextBox("player1", "Player 1", 125, 425, 100, 20, Ogre::ColourValue::White);
	TextRenderer::getSingleton().addTextBox("player2", "Player 2", 470, 425, 100, 20, Ogre::ColourValue::White);
	TextRenderer::getSingleton().addTextBox("scorep1", "0", 125, 445, 100, 20, Ogre::ColourValue::White);
	TextRenderer::getSingleton().addTextBox("scorep2", "0", 470, 445, 100, 20, Ogre::ColourValue::White);

	c=0;
}


bool BilliardCollisionListener::whiteBallPosInUse(Vector3 pos)
{
	for (int i=0;i<9;i++)
	{
		if ((pos-balls[i]->getPosition()).length()<=8)
			return true;
	}
	return false;
}

void BilliardCollisionListener::resetWhiteBall()
{
	ball->setLinearVelocity(0,0,0);
	ball->setAngularVelocity(0,0,0);
	Vector3 position=Vector3(-100,9,0);
	if (whiteBallPosInUse(position))
	{
		for (int p=-140;p<140;p++)
		{
			position=Vector3(p,9,0);
			if (!whiteBallPosInUse(position))
				break;
		}
	}
	ball->setPosition(position);
	ball->setCollisionEnabled(true);
	pocketSoundPlayed[0]=false;
}

void BilliardCollisionListener::resetBalls()
{
	int j=1;
	for (int i=1;i<5;i++)
	{
		balls[i-1]->setPosition(80+8*(i/2),9,4*(i/2)*j);
		j=-j;
	}
	for (int i=5;i<9;i++)
	{
		balls[i-1]->setPosition(80+8*(i/2),9,(8-((i-4)/2)*4)*j);
		j=-j;
	}
	balls[8]->setPosition(96,9,0);
	for (int i=0;i<9;i++)
	{
		balls[i]->setLinearVelocity(0,0,0);
		balls[i]->setAngularVelocity(0,0,0);
		balls[i]->getEntity()->setVisible(true);
		balls[i]->setCollisionEnabled(true);
		pocketSoundPlayed[i+1]=false;
	}
}

//Check whether all the balls are stopped
bool BilliardCollisionListener::ballsStopped()
{
	int i;
	for (i=0;i<9;i++)
	{
		if (balls[i]->getLinearVelocity().length()!=0&&balls[i]->getEntity()->isVisible())
			break;
	}
	
	if (ball->getLinearVelocity().length()==0&&i==9)
	{
		return true;
	}
	else
		return false;
}

void BilliardCollisionListener::handlePlayer()
{
	if(mKeyboard->isKeyDown(OIS::KC_R))
	{
		startGame=false;
		GameRuleManager::getSingleton()->startNewGame();
	}
	TextRenderer::getSingleton().setText("scorep1",
		StringConverter::toString(GameRuleManager::getSingleton()->getScore(PLAYER1)));
	TextRenderer::getSingleton().setText("scorep2",
		StringConverter::toString(GameRuleManager::getSingleton()->getScore(PLAYER2)));
	switch(GameRuleManager::getSingleton()->getCurrentTurn())
	{
	case PLAYER1:
		ogre2dManager->spriteBltFull("currentPlayer.png",-0.8,-0.75,-0.6,-1);
		ogre2dManager->spriteBltFull("playerWaiting.png",0.8,-0.75,0.6,-1);
		break;
	case PLAYER2:
		ogre2dManager->spriteBltFull("playerWaiting.png",-0.8,-0.75,-0.6,-1);
		ogre2dManager->spriteBltFull("currentPlayer.png",0.8,-0.75,0.6,-1);
		break;
	}
	
}

//Adjust the balls' velocities
void BilliardCollisionListener::handleBallVelocities()
{
	if (!startGame)
	{
		resetWhiteBall();
		resetBalls();
	}
	//If the white ball is dropped, take it onto the table and set
	//its velocity to zero.
	if (whiteBallDropped)
		resetWhiteBall();
	
	//If the balls' velocity is less than the threshold of the
	//velocity, then set the velocity to zero. If this is not done, 
	//the physical engine will finally make the balls move extremely
	//slow, but not stopped.
	if (ball->getLinearVelocity().length()<VELOCITY_THRESHOLD)
		ball->setLinearVelocity(0,0,0);
	else
	{
		Vector3 v=ball->getLinearVelocity();
		if (v.y!=0)
			ball->setLinearVelocity(v.x,0,v.z);
		ball->setLinearVelocity(ball->getLinearVelocity()-5*timeSinceLastFrame*ball->getLinearVelocity().normalisedCopy());
	}
	if (ball->getAngularVelocity().length()<VELOCITY_THRESHOLD)
		ball->setAngularVelocity(0,0,0);
	else
		ball->setAngularVelocity(ball->getAngularVelocity()-5*timeSinceLastFrame*ball->getAngularVelocity().normalisedCopy());

	for (int i=0;i<9;i++)
	{
		if (balls[i]->getLinearVelocity().length()<VELOCITY_THRESHOLD)
			balls[i]->setLinearVelocity(0,0,0);
		else
		{
			Vector3 v=balls[i]->getLinearVelocity();
			if (v.y!=0)
				balls[i]->setLinearVelocity(v.x,0,v.z);
			balls[i]->setLinearVelocity(balls[i]->getLinearVelocity()-5*timeSinceLastFrame*balls[i]->getLinearVelocity().normalisedCopy());
		}
		if (balls[i]->getAngularVelocity().length()<VELOCITY_THRESHOLD)
			balls[i]->setAngularVelocity(0,0,0);
		else
			balls[i]->setAngularVelocity(balls[i]->getAngularVelocity()-5*timeSinceLastFrame*balls[i]->getAngularVelocity().normalisedCopy());
	}

}

void BilliardCollisionListener::handleBallCollision()
{
	for (int i=0;i<6;i++)
	{
		if(ball->testCollide(cussions[i]))
			AudioManager::getSingleton()->ballCollideEdge();
	}
	for (int i=0;i<9;i++)
	{
		for (int k=0;k<6;k++)
		{
			if(balls[i]->testCollide(cussions[k]))
				AudioManager::getSingleton()->ballCollideEdge();
		}
		if(ball->testCollide(balls[i])
			&&(ball->getLinearVelocity().length()!=0
			||balls[i]->getLinearVelocity().length()!=0))
		{
			whiteBallDropped=false;
			if (!firstHit)
			{
				firstHit=true;
				GameRuleManager::getSingleton()->hitFirstBall(i+1);
			}
			AudioManager::getSingleton()->ballCollide();
		}
		for (int j=i+1;j<9;j++)
		{
			if (balls[i]->testCollide(balls[j])
				&&(balls[i]->getLinearVelocity().length()!=0
				||balls[j]->getLinearVelocity().length()!=0)
				&&startGame)
			{
				AudioManager::getSingleton()->ballCollide();
			}
		}
	}
	if (ballsStopped())
		firstHit=false;
}

void BilliardCollisionListener::handleBallDropping()
{
	Vector3 tmp=ball->getPosition();
	//If the white ball enter the area of pockets, make it drop under the table.
	if ((tmp.x>-6&&tmp.x<6&&(tmp.z>70||tmp.z<-70))||
		((tmp.x>140||tmp.x<-140)&&(tmp.z>67||tmp.z<-67)))
	{
		//Disable the collision detection of the ball so that it can drop down. 
		ball->setCollisionEnabled(false);
		ball->setLinearVelocity(0,-50,0);
		if(!pocketSoundPlayed[0])
		{
			AudioManager::getSingleton()->ballIntoPocket();
			pocketSoundPlayed[0]=true;
			GameRuleManager::getSingleton()->potABall(0);
		}
	}
	//If the white ball's position is lower than -100 then make it stop.
	if (ball->getPosition().y<-100)
	{
		ball->setLinearVelocity(0,0,0);
		//If all the balls have stopped, set whiteBallDropped to true in order to 
		//reset the white ball's position in the next frame.
		if (ballsStopped())
		{
			ball->setCollisionEnabled(true);
			pocketSoundPlayed[0]=false;
			whiteBallDropped=true;
		}
	}
	
	for (int i=0;i<9;i++)
	{
		tmp=balls[i]->getPosition();
		if ((tmp.x>-6&&tmp.x<6&&(tmp.z>70||tmp.z<-70))||
			((tmp.x>140||tmp.x<-140)&&(tmp.z>67||tmp.z<-67)))
		{
			balls[i]->setCollisionEnabled(false);
			balls[i]->setLinearVelocity(0,-50,0);
			if (!pocketSoundPlayed[i+1])
			{
				AudioManager::getSingleton()->ballIntoPocket();
				pocketSoundPlayed[i+1]=true;
				GameRuleManager::getSingleton()->potABall(i+1);
			}
		}
		if (balls[i]->getPosition().y<-100)
		{
			balls[i]->setLinearVelocity(0,0,0);
			balls[i]->getSceneNode()->setVisible(false);
		}
	}
}

void BilliardCollisionListener::handleObstacle()
{
	/*for (int i=0;i<2;i++)
	{
		std::vector<Vector3> v=bodies[i]->track();
		obstacle[i]->render(v);
	}*/
	std::vector<Vector3> points=bodies[0]->track();
	//Vector3* obstaclePos=getObstaclePosition(TRIANGLE_OBSTACLE);
	Vector3 obstaclePos;
	for (int i=0;i<points.size();i++)
	{
		obstaclePos=obstaclePos+points[i];
	}
	obstaclePos=obstaclePos/points.size();

	//if (obstaclePos!=NULL)
	{
		//obstacle->yaw(-obstacleAngle);
		float obstacleY=obstaclePos.y*RATIO_Y;
		if(obstacleY<15)
			obstacle->setPosition((obstaclePos.x+OFFSET_X)*RATIO_X,15,-(obstaclePos.z+OFFSET_Z)*RATIO_Z);
		else
			obstacle->setPosition((obstaclePos.x+OFFSET_X)*RATIO_X,obstacleY,-(obstaclePos.z+OFFSET_Z)*RATIO_Z);
		
		/*Vector3 v=Vector3(points[1].x-points[0].x,0,points[0].z-points[1].z);
		if (v.length()> 0.01 && abs(v.x)>0.01)
		{
			obstacleAngle=v.angleBetween(Vector3(1,0,0));
			if (points[0].z>points[1].z)
			{
				obstacleAngle=-obstacleAngle;
			}
		}
		
		obstacle->yaw(obstacleAngle);*/
		//delete obstaclePos;
	}
}

void BilliardCollisionListener::handleCamera()
{
	Vector3* camPos=getEyePosition();
	if (camPos!=NULL)
	{
		/*camera->translate(Vector3(-camTrans,0,0));
		camera->yaw(Radian(-camAngle));
		camAngle=-atan(camPos->x/camPos->y);
		camTrans=camPos->x*500;
		camera->yaw(Radian(camAngle));
		camera->translate(Vector3(camTrans,0,0));*/
		delete camPos;
	}
}

void BilliardCollisionListener::handleCue()
{
	isBallHit=false;
	Vector3 **cuePoints = NULL;
	if (isFrameAvailable()) {
		handleCamera();
		handleObstacle();
		if (ballsStopped())
		{
			if (!hitEnded)
			{
				hitEnded=true;
				switch(GameRuleManager::getSingleton()->endHit())
				{
				case GAME_OVER:
					startGame=false;
					//AudioManager::getSingleton()->gameEnd();
					GameRuleManager::getSingleton()->startNewGame();
					break;
				}
			}
			cueNode->setVisible(true);
		//Read the points' position on the cue.
		cuePoints = getCuePoints();
		if (cuePoints != NULL)
		{
			//Calculate the vector of the cue. The z-axis of the real coordinates is 
			//reverse to the z-axis of the game coordinates.
			Vector3 cueVector=Vector3(cuePoints[0]->x-cuePoints[1]->x,
				cuePoints[0]->y-cuePoints[1]->y,cuePoints[1]->z-cuePoints[0]->z);
			//Roll and pitch the cue back to the initial position.
			cueNode->roll(-angleUp);
			cueNode->pitch(-angle);
			//Calculate the angle for pitch
			angle=Vector3(cuePoints[0]->x-cuePoints[1]->x,0,cuePoints[1]->z-cuePoints[0]->z)
				.angleBetween(Vector3(1,0,0));
			if (cuePoints[0]->z>cuePoints[1]->z)
			{
				angle=-angle;
			}
			//Calculate the angle for roll
			angleUp=cueVector.angleBetween(Vector3(cueVector.x,0,cueVector.z));
			if (cuePoints[0]->y<cuePoints[1]->y)
			{
				angleUp=-angleUp;
			}
			float cueY=(cuePoints[0]->y+OFFSET_Y)*RATIO_Y;
			//If the height of the cue's position is too low, set it to the lowest position.
			if(cueY<LOWEST_Y)
				cueNode->setPosition((cuePoints[0]->x+OFFSET_X)*RATIO_X,LOWEST_Y,-(cuePoints[0]->z+OFFSET_Z)*RATIO_Z);
			else
				cueNode->setPosition((cuePoints[0]->x+OFFSET_X)*RATIO_X,cueY,-(cuePoints[0]->z+OFFSET_Z)*RATIO_Z);
			
			//Pitch and roll the cue.
			cueNode->pitch(angle);
			cueNode->roll(angleUp);
			
			Radian ang=(cueNode->getPosition()-ball->getPosition()).angleBetween(cueVector);
			//The distance from the white ball to the cue. 
			float d=(ball->getPosition()-cueNode->getPosition()).length()*sin(ang.valueRadians());
			//The rough position of the touch point between the ball and the cue if the touch happens.
			float touchPosition=(ball->getPosition()-cueNode->getPosition()).length();
			
			if (d<=TOUCH_DISTANCE&&d<lastD[0]&&ang.valueDegrees()<90&&touchPosition<=CUE_LENGTH
				&&touchPosition>=0)
			{
				startGame=true;
				whiteBallDropped=false;
				if (hitEnded)
				{
					mDebugText=StringConverter::toString(++c);
					AudioManager::getSingleton()->hitBall();
					GameRuleManager::getSingleton()->startHit(0);
				}
				//Calculate the ball's velocity according to the change of the position of the touch point.
				ball->setLinearVelocity(
					0.5*(Vector3(cueNode->getPosition().x-touchPosition*cos(angle.valueRadians()),0,
					cueNode->getPosition().z-touchPosition*sin(angle.valueRadians()))
					-Vector3(lastPosition.x-touchPosition*cos(lastAngle.valueRadians()),0,
					lastPosition.z-touchPosition*sin(lastAngle.valueRadians())))
					/timeSinceLastFrame);
				hitEnded=false;
				isBallHit=true;
			}
			lastD[0]=d;
			for (int i=0;i<9;i++)
			{
				ang=(cueNode->getPosition()-balls[i]->getPosition()).angleBetween(cueVector);
				d=(balls[i]->getPosition()-cueNode->getPosition()).length()*sin(ang.valueRadians());
				touchPosition=(balls[i]->getPosition()-cueNode->getPosition()).length();
				if (d<=TOUCH_DISTANCE&&d<lastD[i]&&ang.valueDegrees()<90&&touchPosition<=CUE_LENGTH
					&&touchPosition>=0)
				{
					startGame=true;
					if (hitEnded)
					{
						mDebugText=StringConverter::toString(++c);
						AudioManager::getSingleton()->hitBall();
						GameRuleManager::getSingleton()->startHit(i+1);
					}
					balls[i]->setLinearVelocity(
						0.5*(Vector3(cueNode->getPosition().x-touchPosition*cos(angle.valueRadians()),0,
						cueNode->getPosition().z-touchPosition*sin(angle.valueRadians()))
						-Vector3(lastPosition.x-touchPosition*cos(lastAngle.valueRadians()),0,
						lastPosition.z-touchPosition*sin(lastAngle.valueRadians())))
						/timeSinceLastFrame);
					
					hitEnded=false;
					isBallHit=true;
				}
				lastD[i+1]=d;
			}
			lastPosition=cueNode->getPosition();
			lastAngle=angle;
		}
		else
		{
			//If the position of the points on the cue are not detected, 
			//set the cue to the position in last frame. 
			cueNode->setPosition(lastPosition);
		}
		}
		else
			cueNode->setVisible(false);
	}
	else if(ballsStopped())
	{
		cueNode->setPosition(lastPosition);
	}
	else
		cueNode->setVisible(false);
	
	if (cuePoints != NULL)
	{
		delete cuePoints[0]; delete cuePoints[1]; delete [] cuePoints;
	}
}
