#ifndef OBJECTPOSITION_H
#define OBJECTPOSITION_H

#include "stdafx.h"
#include "nprigidbody.h"

//String getInfo() 
//{
//	if (RB_GetLatestFrame() == NPRESULT_SUCCESS)
//	{
//		float x, y, z, qx, qy, qz, qw, h, a, b;
//		RB_GetRigidBodyLocation(0, &x, &y, &z, &qx, &qy, &qz, &qw, &h, &a, &b);
//		return StringConverter::toString(x) + " " + StringConverter::toString(y) + " " + StringConverter::toString(z);
//	}
//	else
//	{
//		return "";
//	}
//}

bool isFrameAvailable()
{
	return RB_GetLatestFrame() == NPRESULT_SUCCESS;
}

String getFrameMarker()
{
	int count = RB_FrameMarkerCount();
	//return StringConverter::toString(count);
	String ret = "";

	for (int i = 0; i < count; ++i)
	{
		ret += StringConverter::toString(RB_FrameMarkerX(i)) + " ";
	}
	return ret;
}

Vector3** getCuePoints()
{
	/*if (RB_GetLatestFrame() == NPRESULT_SUCCESS && RB_IsRigidBodyTracked(0))*/
	if (RB_IsRigidBodyTracked(0))
	{
		float x, y, z, qx, qy, qz, qw, h, a, b;
		RB_GetRigidBodyLocation(0, &x, &y, &z, &qx, &qy, &qz, &qw, &h, &a, &b);

		float x1 = RB_FrameMarkerX(0), y1 = RB_FrameMarkerY(0), z1 = RB_FrameMarkerZ(0), 
			x2 = RB_FrameMarkerX(1), y2 = RB_FrameMarkerY(1), z2 = RB_FrameMarkerZ(1), 
			x3 = RB_FrameMarkerX(2), y3 = RB_FrameMarkerY(2), z3 = RB_FrameMarkerZ(2);

		/*points[0] = new Vector3(RB_FrameMarkerX(0), RB_FrameMarkerY(0), RB_FrameMarkerZ(0));
		points[1] = new Vector3(RB_FrameMarkerX(1), RB_FrameMarkerY(1), RB_FrameMarkerZ(1));*/

		float d1 = (x1-x)*(x1-x) + (y1-y)*(y1-y) + (z1-z)*(z1-z);
		float d2 = (x2-x)*(x2-x) + (y2-y)*(y2-y) + (z2-z)*(z2-z);
		float d3 = (x3-x)*(x3-x) + (y3-y)*(y3-y) + (z3-z)*(z3-z);

		float g1[] = {d1, x1, y1, z1}, g2[] = {d2, x2, y2, z2}, g3[] = {d3, x3, y3, z3};
		float *gs[] = {g1, g2, g3};
		for (int i = 0; i < 2; ++i) {
			for (int j = i; j < 3; ++j) {
				if (*(gs[i]) > *(gs[j])) {
					float *temp = gs[i];
					gs[i] = gs[j];
					gs[j] = temp;
				}
			}
		}

		Vector3 **points = new Vector3*[2];
		points[0] = new Vector3(gs[2][1], gs[2][2], gs[2][3]);
		points[1] = new Vector3(gs[0][1], gs[0][2], gs[0][3]);
		return points;

	}

	return NULL;
}

//Vector3* getCuePoint1()
//{
//	//return Vector3(0,0,0);
//
//	if (RB_GetLatestFrame() == NPRESULT_SUCCESS)
//	{
//		float x, y, z, qx, qy, qz, qw, h, a, b;
//		RB_GetRigidBodyLocation(0, &x, &y, &z, &qx, &qy, &qz, &qw, &h, &a, &b);
//
//		float x1, y1, z1;
//		RB_GetRigidBodyMarker(0, 0, &x1, &y1, &z1);
//		/*float xc, yc, zc;
//		RB_GetRigidBodyMarker(0, 2, &xc, &yc, &zc);*/
//
//		return new Vector3(x1 + x, y1 + y, z1 + z);
//		/*return Vector3(x, y, z);*/
//	}
//
//	return NULL;
//
//	
//}
//Vector3* getCuePoint2()
//{
//	if (RB_GetLatestFrame() == NPRESULT_SUCCESS)
//	{
//		float x, y, z, qx, qy, qz, qw, h, a, b;
//		RB_GetRigidBodyLocation(0, &x, &y, &z, &qx, &qy, &qz, &qw, &h, &a, &b);
//
//		float x1, y1, z1;
//		RB_GetRigidBodyMarker(0, 1, &x1, &y1, &z1);
//
//		return new Vector3(x1 + x, y1 + y, z1 + z);
//	}
//
//	return NULL;
//}
#endif