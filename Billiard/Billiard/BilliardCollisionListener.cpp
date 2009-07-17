

#include "BilliardCollisionListener.h"
#include "ObjectPosition.h"


BilliardCollisionListener::BilliardCollisionListener(RenderWindow* win, CollideCamera* cam,World* world,
						  ApplicationObject *ball,ApplicationObject *balls[9],ApplicationObject *cueNode,
						  SceneManager* sceneManager)
						  : MyFrameListener(win, cam)
{
	mWorld=world;
	this->ball=ball;
	for (int i=0;i<9;i++)
	{
		this->balls[i]=balls[i];
		visible[i]=true;
	}
	this->cueNode=cueNode;
	//cueNode=sceneManager->getSceneNode("cueNode");
	targetNode=sceneManager->getSceneNode("targetNode");
	lineNode=sceneManager->getSceneNode("lineNode");
	toBall=false;
	stroken=true;
	cueVisible=true;
	white=false;
	dis=(ball->getPosition()-cueNode->getPosition()).length();
	angle=0;
	angleUp=0;
	c=0;
}

bool BilliardCollisionListener::ballsStoped()
{
	int i;
	for (i=0;i<9;i++)
	{
		if (balls[i]->getLinearVelocity().length()!=0&&balls[i]->getEntity()->isVisible())
			break;
	}
	
	if (ball->getLinearVelocity().length()==0&&i==9)
		return true;
	else
		return false;
}

void BilliardCollisionListener::adjustBallVelocities()
{
	if (white)
	{
		ball->setLinearVelocity(0,0,0);
		ball->setPosition(-100,9,0);
	}
	if (ball->getLinearVelocity().length()<0.1)
		ball->setLinearVelocity(0,0,0);
	else
		ball->setLinearVelocity(ball->getLinearVelocity()-5*timeSinceLastFrame*ball->getLinearVelocity().normalisedCopy());
	if (ball->getAngularVelocity().length()<0.1)
		ball->setAngularVelocity(0,0,0);
	else
		ball->setAngularVelocity(ball->getAngularVelocity()-5*timeSinceLastFrame*ball->getAngularVelocity().normalisedCopy());

	for (int i=0;i<9;i++)
	{
		if (balls[i]->getLinearVelocity().length()<0.1)
			balls[i]->setLinearVelocity(0,0,0);
		else
			balls[i]->setLinearVelocity(balls[i]->getLinearVelocity()-5*timeSinceLastFrame*balls[i]->getLinearVelocity().normalisedCopy());
		if (balls[i]->getAngularVelocity().length()<0.1)
			balls[i]->setAngularVelocity(0,0,0);
		else
			balls[i]->setAngularVelocity(balls[i]->getAngularVelocity()-5*timeSinceLastFrame*balls[i]->getAngularVelocity().normalisedCopy());
	}

}

void BilliardCollisionListener::handleBallDropping()
{
	Vector3 tmp=ball->getPosition();
	if ((tmp.x>-6&&tmp.x<6&&(tmp.z>70||tmp.z<-70))||
		((tmp.x>140||tmp.x<-140)&&(tmp.z>67||tmp.z<-67)))
	{
		ball->setCollisionEnabled(false);
		ball->setLinearVelocity(0,-50,0);
		
	}
	if (ball->getPosition().y<-100)
	{
		//mDebugText=StringConverter::toString(ball->getPosition().x);
		ball->setLinearVelocity(0,0,0);
		if (ballsStoped())
		{
			ball->setCollisionEnabled(true);
			//ball->setPosition(-100,9,0);
			white=true;
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
			if (balls[i]->getPosition().y<-100)
			{
				balls[i]->setLinearVelocity(0,0,0);
				balls[i]->getSceneNode()->setVisible(false);
				visible[i]=false;
			}
		}
	}
}

void BilliardCollisionListener::handleAiming()
{
	//if (mKeyboard->isKeyDown(OIS::KC_EQUALS))
	//{
	//	//mDebugText=StringConverter::toString(lineNode->);
	//	angle+=0.02*40*timeSinceLastFrame;
	//	cueNode->setPosition(ball->getPosition().x-124*cos(angle),-50,ball->getPosition().z-124*sin(angle));
	//	cueNode->pitch(Radian(0.02*40*timeSinceLastFrame));
	//	targetNode->setPosition(ball->getPosition().x+124*cos(angle),9,ball->getPosition().z+124*sin(angle));
	//	lineNode->setPosition(ball->getPosition().x+100*cos(angle),0,ball->getPosition().z+100*sin(angle));
	//	lineNode->yaw(Radian(-0.02*40*timeSinceLastFrame));
	//}
	//if (mKeyboard->isKeyDown(OIS::KC_MINUS))
	//{
	//	angle-=0.02*40*timeSinceLastFrame;
	//	cueNode->setPosition(ball->getPosition().x-124*cos(angle),-50,ball->getPosition().z-124*sin(angle));
	//	cueNode->pitch(Radian(-0.02*40*timeSinceLastFrame));
	//	targetNode->setPosition(ball->getPosition().x+124*cos(angle),9,ball->getPosition().z+124*sin(angle));
	//	lineNode->setPosition(ball->getPosition().x+100*cos(angle),0,ball->getPosition().z+100*sin(angle));
	//	lineNode->yaw(Radian(+0.02*40*timeSinceLastFrame));
	//}

}

void BilliardCollisionListener::handleCue()
{
	cueNode->setLinearVelocity(0,0,0);
	cueNode->setAngularVelocity(0,0,0);

	Vector3 **tmp = NULL;
	if (isFrameAvailable()) {
		tmp = getCuePoints();
		if (tmp != NULL)
		{
			cueNode->roll(-angleUp);
			cueNode->pitch(-angle);
			Radian tmpAngle=Vector3(tmp[0]->x-tmp[1]->x,0,tmp[1]->z-tmp[0]->z).angleBetween(Vector3(1,0,0));
			if (tmp[0]->z>tmp[1]->z)
			{
				tmpAngle=-tmpAngle;
			}
			/*if (abs(tmpAngle.valueDegrees()-angle.valueDegrees())<100||angle.valueDegrees()==0
				||abs(tmpAngle.valueDegrees())+abs(angle.valueDegrees())>340)*/
			//{
				angle=tmpAngle;
			//}
			tmpAngle=Vector3(tmp[0]->x-tmp[1]->x,tmp[0]->y-tmp[1]->y,tmp[1]->z-tmp[0]->z)
				.angleBetween(Vector3(tmp[0]->x-tmp[1]->x,0,tmp[1]->z-tmp[0]->z));
			angleUp=tmpAngle;
			if (tmp[0]->y<tmp[1]->y)
			{
				angleUp=-angleUp;
			}

			//mDebugText=StringConverter::toString(tmp[0]->x)+" "+StringConverter::toString(tmp[0]->y)+" "+StringConverter::toString(tmp[0]->z);
			//mDebugText=StringConverter::toString(angle.valueDegrees());
			cueNode->setPosition(tmp[0]->x*500-62*cos((float)angle.valueRadians()),
				9-62*sin((float)angleUp.valueRadians()),
				-tmp[0]->z*294-62*sin((float)angle.valueRadians()));
			mDebugText=StringConverter::toString(angle.valueDegrees())+" "+StringConverter::toString(angleUp.valueDegrees());
			lastPosition=cueNode->getPosition();

			cueNode->pitch(angle);
			cueNode->roll(angleUp);

			/*if (Vector3(tmp[0]->x-ball->getPosition().x,ball->getPosition().y,-tmp[0]->z-ball->getPosition().z).length()<=120)
			{
				ball->setLinearVelocity(400,0,0);
			}*/
		}
		else
		{
			//mDebugText = "null";
			cueNode->setPosition(lastPosition);
		}
	}
	else
	{
		//mDebugText = "not available";
		cueNode->setPosition(lastPosition);
	}

	
	/*if (ballsStoped())
	{
		cueNode->setVisible(true);
		targetNode->setVisible(true);
		lineNode->setVisible(true);
		cueVisible=true;
		if(stroken)
		{
			cueNode->setPosition(ball->getPosition().x-124*cos(angle),-50,ball->getPosition().z-124*sin(angle));
			targetNode->setPosition(ball->getPosition().x+124*cos(angle),9,ball->getPosition().z+124*sin(angle));
			lineNode->setPosition(ball->getPosition().x+100*cos(angle),0,ball->getPosition().z+100*sin(angle));
		}
	}
	else
	{
		cueNode->setVisible(false);
		targetNode->setVisible(false);
		lineNode->setVisible(false);
		cueVisible=false;
	}*/

	
	if (tmp != NULL)
	{
		delete tmp[0]; delete tmp[1]; delete [] tmp;
	}
}

void BilliardCollisionListener::handleStriking()
{
	//if (mKeyboard->isKeyDown(OIS::KC_SPACE))
	//{
	//	if (cueVisible)
	//	{
	//		stroken=false;
	//		if(!toBall)
	//			cueNode->translate(Vector3(-cos(angle),0,-sin(angle))*40*timeSinceLastFrame);
	//		else
	//			cueNode->translate(Vector3(cos(angle),0,sin(angle))*40*timeSinceLastFrame);
	//		Vector3 tmp(ball->getPosition()-cueNode->getPosition());
	//		//mDebugText=StringConverter::toString(tmp.length())+" "+StringConverter::toString(dis);
	//		if (tmp.length()<=dis||tmp.length()>=dis+40)
	//			toBall=!toBall;
	//		cuePosition=cueNode->getPosition();
	//	}
	//}
	//else if(!stroken)
	//{
	//	Vector3 tmp(ball->getPosition()-cueNode->getPosition());
	//	if (tmp.length()>=dis)
	//	{
	//		cueNode->translate(Vector3(6*cos(angle),0,6*sin(angle))*40*timeSinceLastFrame);
	//	}
	//	else
	//	{
	//		white=false;
	//		ball->setLinearVelocity(Vector3(ball->getPosition().x-cuePosition.x,0,
	//			ball->getPosition().z-cuePosition.z).normalisedCopy() * 400 
	//			* ((ball->getPosition()-cuePosition).length()-dis)/40);
	//		stroken=true;
	//		toBall=false;
	//	}
	//}

}