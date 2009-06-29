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

#include "OgreReferenceAppLayer.h"

#include "ExampleRefAppApplication.h"
#include "OgreStringConverter.h"

// Hacky globals
ApplicationObject *ball;
ApplicationObject *balls[9];

SceneNode* targetNode;
RaySceneQuery* rsq = 0;


// Event handler to add ability to alter curvature
class BspCollisionListener : public ExampleRefAppFrameListener
{
protected:
public:
    BspCollisionListener(RenderWindow* win, CollideCamera* cam)
        : ExampleRefAppFrameListener(win, cam)
    {
    }

	bool frameStarted(const FrameEvent& evt)
	{
		//mDebugText=StringConverter::toString(ball->getBounceVelocityThreshold());
		mDebugText=StringConverter::toString(ball->getLinearVelocity().length());
		if (ball->getLinearVelocity().length()<0.1)
			ball->setLinearVelocity(0,0,0);
		else
			ball->addForce(ball->getLinearVelocity().normalisedCopy()*(-10));
			//ball->setLinearVelocity(ball->getLinearVelocity()-0.1*ball->getLinearVelocity().normalisedCopy());
		return true;
	}

    bool frameEnded(const FrameEvent& evt)
    {
        // local just to stop toggles flipping too fast
        static Real timeUntilNextToggle = 0;

        // Deal with time delays that are too large
        // If we exceed this limit, we ignore
        static const Real MAX_TIME_INCREMENT = 0.5f;
        if (evt.timeSinceLastEvent > MAX_TIME_INCREMENT)
        {
            return true;
        }
        
        if (timeUntilNextToggle >= 0) 
            timeUntilNextToggle -= evt.timeSinceLastFrame;

        // Call superclass
        bool ret = ExampleRefAppFrameListener::frameEnded(evt);        

		if (mKeyboard->isKeyDown(OIS::KC_SPACE) && timeUntilNextToggle <= 0)
        {
            timeUntilNextToggle = 2;
            //ball->setPosition(mCamera->getPosition() + 
                //mCamera->getDirection() * mCamera->getNearClipDistance() * 2);
			
			//if ((ball->getPosition()-mCamera->getPosition()).length()<50)
			{
				
				ball->setLinearVelocity((balls[0]->getPosition()-ball->getPosition()).normalisedCopy() * 200);
				ball->setAngularVelocity(Vector3::ZERO);
				//ball->setFriction(Math::POS_INFINITY); 
			}
            
        }

        // Move the targeter
        /*rsq->setRay(mCamera->getRealCamera()->getCameraToViewportRay(0.5, 0.5));
        RaySceneQueryResult& rsqResult = rsq->execute();
        RaySceneQueryResult::iterator ri = rsqResult.begin();
        if (ri != rsqResult.end())
        {
            RaySceneQueryResultEntry& res = *ri;
            targetNode->setPosition(rsq->getRay().getPoint(res.distance));

        }*/
        return ret;
    }
};

class BspCollisionApplication : public ExampleRefAppApplication
{
public:
    BspCollisionApplication() {
    
    }

    ~BspCollisionApplication() 
    {
		delete rsq;
    }

protected:
    
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

		/*l = mSceneMgr->createLight("MainLight1");
		l->setPosition(-50, 650,480);
		l->setAttenuation(8000,1,0,0);*/


        // Setup World
		//mWorld->_applyCollision();
        mWorld->setGravity(Vector3(0, -1000, 0));
		
       // mWorld->getSceneManager()->setWorldGeometry("terrain.cfg");

        // modify camera for close work
        mCamera->setNearClipDistance(10);
        mCamera->setFarClipDistance(20000);
		mCamera->setPosition(0, 500, 0);
		mCamera->pitch(Degree(-90));
		//mCamera->yaw(Degree(-90));

		//Entity *mEntity =mWorld->getSceneManager()->createEntity( "Robot", "robot.mesh" );

		//// Create the scene node
		//SceneNode *mNode = mWorld->getSceneManager()->getRootSceneNode( )->
		//	createChildSceneNode( "RobotNode", Vector3( 200, 60, 580) );
		//mNode->attachObject( mEntity );
		
		//ApplicationObject *robot=mWorld->createOgreObject("head","robot.mesh",Vector3(200,60,580));
		//robot->CollisionProxyList[0]
		
        ball = mWorld->createBall("ball", 4,Vector3(-100, 69, 0)); //vp.position + Vector3(0,0,80));
        ball->setDynamicsEnabled(true);
        ball->getEntity()->setMaterialName("WhiteBall");
		ball->setMassSphere(1,4);
		ball->setBounceParameters(1.0,0.5);

		int j=1;
		for (int i=1;i<5;i++)
		{
			balls[i-1] =mWorld->createBall("ball"+StringConverter::toString(i),4,Vector3(80+8*(i/2),69,4*(i/2)*j));
			balls[i-1]->setDynamicsEnabled(true);
			balls[i-1]->getEntity()->setMaterialName("Ball"+StringConverter::toString(i));
			balls[i-1]->setMassSphere(1,4);
			balls[i-1]->setBounceParameters(1.0,0.5);
			j=-j;
		}
		for (int i=5;i<9;i++)
		{
			balls[i-1] =mWorld->createBall("ball"+StringConverter::toString(i),4,Vector3(80+8*(i/2),69,(8-((i-4)/2)*4)*j));
			balls[i-1]->setDynamicsEnabled(true);
			balls[i-1]->getEntity()->setMaterialName("Ball"+StringConverter::toString(i));
			balls[i-1]->setMassSphere(1,4);
			balls[i-1]->setBounceParameters(1.0,0.5);
			j=-j;
		}
		balls[8] =mWorld->createBall("ball9",4,Vector3(96,69,0));
		balls[8]->setDynamicsEnabled(true);
		balls[8]->getEntity()->setMaterialName("Ball9");
		balls[8]->setMassSphere(1,4);
		balls[8]->setBounceParameters(1.0,0.5);
		
		OgreRefApp::Box* box= mWorld->createBox("table", 354,10,177, Vector3(0,60,0));
        box->getEntity()->setMaterialName("Billiards");

		box=mWorld->createBox("top",10,5,177,Vector3(172,67.5,0));
		box->getEntity()->setMaterialName("Examples/Rocky");
		
		box=mWorld->createBox("bottom",10,5,177,Vector3(-172,67.5,0));
		box->getEntity()->setMaterialName("Examples/Rocky");

		box=mWorld->createBox("left",354,5,10,Vector3(0,67.5,-83.5));
		box->getEntity()->setMaterialName("Examples/Rocky");

		box=mWorld->createBox("right",354,5,10,Vector3(0,67.5,83.5));
		box->getEntity()->setMaterialName("Examples/Rocky");

		mWorld->_applyCollision();
        mCamera->setCollisionEnabled(false);
        mCamera->getRealCamera()->setQueryFlags(0);
    }
    // Create new frame listener
    void createFrameListener(void)
    {
        mFrameListener= new BspCollisionListener(mWindow, mCamera);
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







