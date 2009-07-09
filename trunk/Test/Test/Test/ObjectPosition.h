#ifndef OBJECTPOSITION_H
#define OBJECTPOSITION_H

#include "stdafx.h"
#include "nprigidbody.h"

Vector3 getCuePoint1()
{
	//return Vector3(0,0,0);
	float x, y, z;
	RB_GetRigidBodyMarker(0, 0, &x, &y, &z);
	float xc, yc, zc;
	RB_GetRigidBodyMarker(0, 2, &xc, &yc, &zc);

	return Vector3(xc + x, yc + y, zc + z);
}
Vector3 getCuePoint2()
{
	/*return Vector3(1,0,1);*/
	float x, y, z;
	RB_GetRigidBodyMarker(0, 1, &x, &y, &z);
	float xc, yc, zc;
	RB_GetRigidBodyMarker(0, 2, &xc, &yc, &zc);

	return Vector3(xc + x, yc + y, zc + z);
}
#endif