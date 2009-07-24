#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle
{
private:
	ApplicationObject** plane;
	Vector3 pos;
	bool initialized;
	World* world;
	int numOfPlane;
	Radian* angle;
	//Vector3** points;
public:
	Obstacle(World* mWorld,int numOfPlane,String name)
	{
		this->world=mWorld;
		this->numOfPlane=numOfPlane;
		plane=new ApplicationObject*[numOfPlane];
		for (int i=0;i<numOfPlane;i++)
		{
			plane[i]=world->createBox(name+StringConverter::toString(i),25,20,0.1,
				Vector3(0,0,0));
			plane[i]->getEntity()->setMaterialName("Billiards/Wood");
		}
		angle=new Radian[numOfPlane];
	}
	
	void render(std::vector<Vector3> points)
	{
		for(int i=0;i<numOfPlane;i++)
		{
			plane[i]->yaw(-angle[i]);
			int j=(i+1)%numOfPlane;
			Vector3 tmpPos=Vector3(((points[i].x+points[j].x)/2+0.03)*500,15,((-points[i].z-points[j].z)/2+0.01)*500);
			plane[i]->setPosition(tmpPos);
			angle[i]=Vector3(points[j].x-points[i].x,0,points[i].z-points[j].z).angleBetween(Vector3(1,0,0));
			if (points[i].z>points[j].z)
			{
				angle[i]=-angle[i];
			}
			plane[i]->yaw(angle[i]);
		}
	}
	//void setPosition(Real x, Real y, Real z)
	//{
	//	plane[0]->setPosition(Vector3(x,y,z+10*sin(Degree(60).valueRadians())));
	//	plane[1]->setPosition(Vector3(x-5,y,z));
	//	plane[2]->setPosition(Vector3(x+5,y,z));
	//	pos=Vector3(x,y,z);
	//}
	//void setPosition(Vector3 position)
	//{
	//	this->setPosition(position.x,position.y,position.z);
	//}
	//void yaw(Radian angle)
	//{
	//	plane[0]->->yaw(angle,SceneNode::TS_LOCAL);
	//	/*Vector3 tmpPos=pos;
	//	this->setPosition(0,0,0);
	//	for (int i=0;i<3;i++)
	//	{
	//	plane[i]->getSceneNode()->yaw(angle,SceneNode::TS_WORLD);
	//	}
	//	this->setPosition(tmpPos);*/
	//}
};

#endif