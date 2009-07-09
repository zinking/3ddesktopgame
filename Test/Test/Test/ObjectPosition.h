#ifndef OBJECTPOSITION_H
#define OBJECTPOSITION_H

#include "stdafx.h"
#include "nprigidbody.h"

Vector3 getCuePoint1()
{
	//return Vector3(0,0,0);
	float x, y, z;
	RB_GetRigidBodyMarker(0, 0, &x, &y, &z);
	return Vector3(x, y, z);
}
Vector3 getCuePoint2()
{
	/*return Vector3(1,0,1);*/
	float x, y, z;
	RB_GetRigidBodyMarker(0, 1, &x, &y, &z);
	return Vector3(x, y, z);
}
#endif