/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2006 Torus Knot Software Ltd
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
LGPL like the rest of the engine.
-----------------------------------------------------------------------------
*/

/*
-----------------------------------------------------------------------------
Filename:    BspCollision.cpp
Description: Somewhere to play in the sand...
-----------------------------------------------------------------------------
*/

#include "stdafx.h"
#include "BilliardCollisionListener.h"

// Hacky globals


class BspCollisionApplication : public ExampleRefAppApplication
{
public:
	BspCollisionApplication() {

	}

	~BspCollisionApplication() 
	{
		//delete rsq;
	}

protected:
	ApplicationObject *ball;
	ApplicationObject *balls[9];
	ApplicationObject *cueNode;
	SceneNode* targetNode;
	SceneNode* lineNode;

	void chooseSceneManager(void)
	{
		mSceneMgr = mRoot->createSceneManager(ST_EXTERIOR_CLOSE);
	}
	void createWorld(void)
	{
		// Create BSP-specific world
		mWorld = new World(mSceneMgr, World::WT_REFAPP_GENERIC);
	}
	void createScene(void)
	{
		mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
		// Set ambient light
		mSceneMgr->setAmbientLight(ColourValue(1.0, 1.0, 1.0));
		// Create a point light
		Light* l = mSceneMgr->createLight("MainLight");
		l->setPosition(50, 650, -480);
		l->setAttenuation(8000,1,0,0);

		// Setup World
		mWorld->setGravity(Vector3(0, -1000, 0));

		// modify camera for close work
		mCamera->setNearClipDistance(10);
		mCamera->setFarClipDistance(20000);
		mCamera->setPosition(0, 500, 0);
		mCamera->pitch(Degree(-90));
		//mCamera->yaw(Degree(-90));

		ball = mWorld->createBall("ball", 4,Vector3(-100, 9, 0));
		ball->setDynamicsEnabled(true);
		ball->getEntity()->setMaterialName("WhiteBall");
		ball->setMassSphere(1,4);
		ball->setBounceParameters(1.0,0.5);

		Entity* bas = mSceneMgr->createEntity("bas","bas.mesh");
		SceneNode* basNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		bas->setMaterialName("Billiards/Bas");
		basNode->attachObject(bas);
		basNode->scale(3,3,3);
		basNode->setPosition(-0.5,7,0);

		Entity* targetEnt = mSceneMgr->createEntity("target", "sphere.mesh");
		MaterialPtr mat = MaterialManager::getSingleton().create("targeter", 
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		Pass* pass = mat->getTechnique(0)->getPass(0);
		TextureUnitState* tex = pass->createTextureUnitState();
		tex->setColourOperationEx(LBX_SOURCE1, LBS_MANUAL, LBS_CURRENT, 
			ColourValue::Red);
		pass->setLightingEnabled(false);
		pass->setSceneBlending(SBT_ADD);
		pass->setDepthWriteEnabled(false);

		targetEnt->setMaterialName("targeter");
		targetEnt->setCastShadows(false);
		targetEnt->setQueryFlags(0);
		targetNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("targetNode");
		targetNode->scale(0.04, 0.04, 0.04);
		targetNode->attachObject(targetEnt);
		
		Ogre::ManualObject* line=mSceneMgr->createManualObject("line");
		line->begin("",Ogre::RenderOperation::OT_LINE_LIST);
		//line->position(ball->getPosition().x,9,0);
		for (int i=1;i<124;i+=4)
		{
			line->position(ball->getPosition().x+i,9,0);
		}
		line->end();
		lineNode=mSceneMgr->getRootSceneNode()->createChildSceneNode("lineNode");
		lineNode->attachObject(line);

		int j=1;
		for (int i=1;i<5;i++)
		{
			balls[i-1] =mWorld->createBall("ball"+StringConverter::toString(i),4,Vector3(80+8*(i/2),9,4*(i/2)*j));
			balls[i-1]->setDynamicsEnabled(true);
			balls[i-1]->getEntity()->setMaterialName("Ball"+StringConverter::toString(i));
			balls[i-1]->setMassSphere(1,4);
			balls[i-1]->setBounceParameters(1.0,0.5);
			balls[i-1]->pitch(Degree(60));
			j=-j;
		}
		for (int i=5;i<9;i++)
		{
			balls[i-1] =mWorld->createBall("ball"+StringConverter::toString(i),4,Vector3(80+8*(i/2),9,(8-((i-4)/2)*4)*j));
			balls[i-1]->setDynamicsEnabled(true);
			balls[i-1]->getEntity()->setMaterialName("Ball"+StringConverter::toString(i));
			balls[i-1]->setMassSphere(1,4);
			balls[i-1]->setBounceParameters(1.0,0.5);
			j=-j;
		}
		balls[8] =mWorld->createBall("ball9",4,Vector3(96,9,0));
		balls[8]->setDynamicsEnabled(true);
		balls[8]->getEntity()->setMaterialName("Ball9");
		balls[8]->setMassSphere(1,4);
		balls[8]->setBounceParameters(1.0,0.5);

		cueNode = mWorld->createOgreObject("cue","cue.mesh",2,2,124,Vector3(0,9,0));
		//cueNode->setDynamicsEnabled(true);
		cueNode->getEntity()->setMaterialName("Billiards/Cue");
		cueNode->setMassBox(10,Vector3(4,4,124));
		cueNode->roll(Degree(-90));

		OgreRefApp::OgreObject* table=mWorld->createOgreObject("table","table1.mesh",300,10,147,Vector3(-0.5,0,0));
		table->getEntity()->setMaterialName("Billiards/Table");
		table->pitch(Degree(90));
		table->getSceneNode()->scale(0.98,1,1);

		



		/*OgreRefApp::Box* box= mWorld->createBox("table", 300,10,147, Vector3(0,0,0));
		box->getEntity()->setMaterialName("Billiards/Table");*/

		OgreRefApp::Box* box=mWorld->createBox("top",5,15,132,Vector3(150,2.5,0));
		box->getEntity()->setMaterialName("Billiards/Table");

		box=mWorld->createBox("topout",15,15,187,Vector3(160,2.5,0));
		box->getEntity()->setMaterialName("Billiards/Wood");

		box=mWorld->createBox("bottom",5,15,132,Vector3(-150,2.5,0));
		box->getEntity()->setMaterialName("Billiards/Table");

		box=mWorld->createBox("bottomout",15,15,187,Vector3(-160,2.5,0));
		box->getEntity()->setMaterialName("Billiards/Wood");

		box=mWorld->createBox("lefttop",135,15,5,Vector3(73.5,2.5,-76));
		box->getEntity()->setMaterialName("Billiards/Table");

		box=mWorld->createBox("leftbottom",135,15,5,Vector3(-73.5,2.5,-76));
		box->getEntity()->setMaterialName("Billiards/Table");

		box=mWorld->createBox("leftout",305,15,15,Vector3(0,2.5,-86));
		box->getEntity()->setMaterialName("Billiards/Wood");

		box=mWorld->createBox("righttop",135,15,5,Vector3(73.5,2.5,76));
		box->getEntity()->setMaterialName("Billiards/Table");

		box=mWorld->createBox("rightbottom",135,15,5,Vector3(-73.5,2.5,76));
		box->getEntity()->setMaterialName("Billiards/Table");

		box=mWorld->createBox("rightout",305,15,15,Vector3(0,2.5,86));
		box->getEntity()->setMaterialName("Billiards/Wood");

		mWorld->_applyCollision();
		mCamera->setCollisionEnabled(false);
		mCamera->getRealCamera()->setQueryFlags(0);
	}
	// Create new frame listener
	void createFrameListener(void)
	{
		mFrameListener= new BilliardCollisionListener(mWindow, mCamera,mWorld,ball,balls,cueNode,mSceneMgr);
		mRoot->addFrameListener(mFrameListener);
	}

public:

};



#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"


INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main(int argc, char **argv)
#endif
{

	SetProjectorViewport(SCREEN_LEFT, SCREEN_RIGHT,SCREEN_BOTTOM, SCREEN_TOP);
	SetNearClipDistance(0.0001);
	RB_InitializeRigidBody();
	RB_LoadProfile("cal.cal");
	RB_LoadDefinition("rbd.rdef");
	RB_StartCameras();

	// Create application object
	BspCollisionApplication app;

	try {
		app.go();
	} catch( Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		std::cerr << "An exception has occured: " << e.getFullDescription();
#endif
	}


	return 0;
}







