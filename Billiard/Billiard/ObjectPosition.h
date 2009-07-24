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
		/*float x, y, z, qx, qy, qz, qw, heading, attitude, bank;
		RB_GetRigidBodyLocation(CUE_INDEX, &x, &y, &z, &qx, &qy, &qz, &qw, &heading, &attitude, &bank);

		float m[4][4];
		float xx, xy, xz, xw, yy, yz, yw, zz, zw;
		xx = qx * qx; xy = qx * qy; xz = qx * qz; xw = qx * qw;
		yy = qy * qy; yz = qy * qz; yw = qy * qw; zz = qz * qz; zw = qz * qw;

		m[0][0]  = 1 - 2 * ( yy + zz );
		m[0][1]  =     2 * ( xy - zw );
		m[0][2] =     2 * ( xz + yw );

		m[1][0]  =     2 * ( xy + zw );
		m[1][1]  = 1 - 2 * ( xx + zz );
		m[1][2]  =     2 * ( yz - xw );

		m[2][0]  =     2 * ( xz - yw );
		m[2][1]  =     2 * ( yz + xw );
		m[2][2] = 1 - 2 * ( xx + yy );

		m[0][3]=x;
		m[1][3]=y;
		m[2][3]=z;

		m[3][0] = m[3][1] = m[3][2] = 0;
		m[3][3] = 1;

		float left[4];
		RB_GetRigidBodyMarker(CUE_INDEX,0,&left[0],&left[1],&left[2]);
		left[3]=1;

		float right[4];
		RB_GetRigidBodyMarker(CUE_INDEX,2,&right[0],&right[1],&right[2]);
		right[3]=1;

		float nleft[4];
		float nright[4];

		for(int i=0; i<4; i++)
		{
			float t1=0;
			float t2=0;
			for(int j=0; j<4; j++)
			{
				t1+=m[i][j]*left[j];
				t2+=m[i][j]*right[j];
			}
			nleft[i]=t1;
			nright[i]=t2;
		}

		Vector3 **points = new Vector3*[2];
		points[0] = new Vector3(nleft[0], nleft[1], nleft[2]);
		points[1] = new Vector3(nright[0], nright[1], nright[2]);
		return points;*/

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
	/*if (RB_IsRigidBodyTracked(index))
	{
		float x, y, z, qx, qy, qz, qw, h, a, b;
		RB_GetRigidBodyLocation(index, &x, &y, &z, &qx, &qy, &qz, &qw, &h, &a, &b);
		return new Vector3(x, y, z);
	}
	return NULL;*/
	return RigidBody::getPosition(index);
}

Vector3* getEyePosition()
{
	/*if (RB_IsRigidBodyTracked(EYE_INDEX))
	{
		float x, y, z, qx, qy, qz, qw, h, a, b;
		RB_GetRigidBodyLocation(EYE_INDEX, &x, &y, &z, &qx, &qy, &qz, &qw, &h, &a, &b);
		return new Vector3(x, y, z);
	}
	return NULL;*/
	return RigidBody::getPosition(EYE_INDEX);
}



#endif