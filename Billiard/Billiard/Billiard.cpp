
#include "stdafx.h"
#include "BilliardCollisionListener.h"
#include "AudioManager.h"

class BspCollisionApplication : public ExampleRefAppApplication
{
public:
	BspCollisionApplication() 
	{
	}

	~BspCollisionApplication() 
	{
	}

protected:
	//The white ball
	ApplicationObject *ball;
	//The other nine balls
	ApplicationObject *balls[9];
	//Obstacle *obstacle[2];
	ApplicationObject *cussions[6];
	ApplicationObject *obstacle;
	SceneNode *cueNode;
	RigidBody* bodies[2];

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
		mCamera->setPosition(0, 325, 0);
		mCamera->pitch(Degree(-90));
		mCamera->setFixedYawAxis(true,Vector3::UNIT_Z);
		//mCamera->yaw(Degree(-90));
		
		//Create the white ball
		ball = mWorld->createBall("ball", 4,Vector3(-100, 9, 0));
		ball->setDynamicsEnabled(true);
		ball->getEntity()->setMaterialName("WhiteBall");
		ball->setMassSphere(1,4);
		ball->setBounceParameters(1.0,0.5);

		//Create the other nine balls
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
		
		//Create the cue
		Entity* cue = mSceneMgr->createEntity("cue","cue.mesh");
		cueNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("cueNode");
		cue->setMaterialName("Billiards/Cue");
		cueNode->attachObject(cue);
		cueNode->roll(Degree(-90));
		cueNode->setPosition(-150,9,0);

		//Create the table
		OgreRefApp::OgreObject* table=mWorld->createOgreObject("table","table1.mesh",300,10,147,Vector3(-0.5,0,0));
		table->getEntity()->setMaterialName("Billiards/Table");
		table->pitch(Degree(90));
		table->getSceneNode()->scale(0.98,1,1);
		
		//Create the pocket
		Entity* pocket = mSceneMgr->createEntity("bas","bas.mesh");
		SceneNode* pocketNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		pocket->setMaterialName("Billiards/Bas");
		pocketNode->attachObject(pocket);
		pocketNode->scale(3,3,3);
		pocketNode->setPosition(-0.5,7,0);

		//Create the cushions
		OgreRefApp::Box* box=mWorld->createBox("cussion0",5,15,132,Vector3(150,2.5,0));
		box->getEntity()->setMaterialName("Billiards/Table");
		cussions[0]=box;

		box=mWorld->createBox("topout",15,15,187,Vector3(160,2.5,0));
		box->getEntity()->setMaterialName("Billiards/Wood");

		box=mWorld->createBox("cussion1",5,15,132,Vector3(-150,2.5,0));
		box->getEntity()->setMaterialName("Billiards/Table");
		cussions[1]=box;

		box=mWorld->createBox("bottomout",15,15,187,Vector3(-160,2.5,0));
		box->getEntity()->setMaterialName("Billiards/Wood");

		box=mWorld->createBox("cussion2",135,15,5,Vector3(73.5,2.5,-76));
		box->getEntity()->setMaterialName("Billiards/Table");
		cussions[2]=box;

		box=mWorld->createBox("cussion3",135,15,5,Vector3(-73.5,2.5,-76));
		box->getEntity()->setMaterialName("Billiards/Table");
		cussions[3]=box;

		box=mWorld->createBox("leftout",305,15,15,Vector3(0,2.5,-86));
		box->getEntity()->setMaterialName("Billiards/Wood");

		box=mWorld->createBox("cussion4",135,15,5,Vector3(73.5,2.5,76));
		box->getEntity()->setMaterialName("Billiards/Table");
		cussions[4]=box;

		box=mWorld->createBox("cussion5",135,15,5,Vector3(-73.5,2.5,76));
		box->getEntity()->setMaterialName("Billiards/Table");
		cussions[5]=box;

		box=mWorld->createBox("rightout",305,15,15,Vector3(0,2.5,86));
		box->getEntity()->setMaterialName("Billiards/Wood");

		bodies[0]=new RigidBody(TRIANGLE_OBSTACLE);
		//bodies[1]=new RigidBody(SQUARE_OBSTACLE);
		/*obstacle[0]=new Obstacle(mWorld,bodies[0]->getVertexCount(),"triangle");
		obstacle[1]=new Obstacle(mWorld,bodies[1]->getVertexCount(),"square");*/

		obstacle=mWorld->createBox("obstacle",20,20,20,Vector3(0,0,0));
		obstacle->getEntity()->setMaterialName("Billiards/Obstacle");

		mWorld->_applyCollision();
		mCamera->setCollisionEnabled(false);
		mCamera->getRealCamera()->setQueryFlags(0);

		AudioManager::getSingleton()->playBackgroundMusic();
	}
	// Create new frame listener
	void createFrameListener(void)
	{
		mFrameListener= new BilliardCollisionListener(mWindow, mCamera,mWorld,bodies);
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

	//SetProjectorViewport(SCREEN_LEFT, SCREEN_RIGHT,SCREEN_BOTTOM, SCREEN_TOP);
	//SetNearClipDistance(0.0001);
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