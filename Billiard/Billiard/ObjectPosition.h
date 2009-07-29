#ifndef OBJECTPOSITION_H
#define OBJECTPOSITION_H

#include "stdafx.h"
#include "nprigidbody.h"

bool isFrameAvailable()
{
	return RB_GetLatestFrame() == NPRESULT_SUCCESS;
}

Vector3** getCuePoints()
{
	if (RB_IsRigidBodyTracked(CUE_INDEX))
	{
		float m[4][4], c[4];
		RigidBody::getTransformMatrix(CUE_INDEX, m);

		Vector3 **points = new Vector3*[2];
		RigidBody::getCoordinate(CUE_INDEX, 0, m, c);
		points[0] = new Vector3(c[0], c[1], c[2]);
		RigidBody::getCoordinate(CUE_INDEX, 2, m, c);
		points[1] = new Vector3(c[0], c[1], c[2]);

		return points;
	}

	return NULL;
}

Vector3* getObstaclePosition(const int index)
{
	return RigidBody::getPosition(index);
}

Vector3* getEyePosition()
{
	return RigidBody::getPosition(EYE_INDEX);
}

#endif