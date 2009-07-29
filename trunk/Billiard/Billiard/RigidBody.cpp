
#include "RigidBody.h"

RigidBody::RigidBody(const int index)
					: rbIndex(index), 
					vertices(RB_GetRigidBodyMarkerCount(index))
{
}

int RigidBody::getVertexCount() const
{
	return vertices.size();
}

vector<Vector3> &RigidBody::track()
{
	if (RB_IsRigidBodyTracked(rbIndex))
	{
		int markerCount = this->vertices.size();
		float m[4][4], c[4];
		RigidBody::getTransformMatrix(rbIndex, m);
		for (int i = 0; i < markerCount; ++i)
		{
			RigidBody::getCoordinate(rbIndex, i, m, c);
			vertices[i].x = c[0];
			vertices[i].y = c[1];
			vertices[i].z = c[2];
		}
	}
	return vertices;
}

void RigidBody::getTransformMatrix(const int index, float (*m)[4])
{
	float x, y, z, qx, qy, qz, qw, heading, attitude, bank;
	RB_GetRigidBodyLocation(index, &x, &y, &z, &qx, &qy, &qz, &qw, &heading, &attitude, &bank);

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

	m[0][3] = x;
	m[1][3] = y;
	m[2][3] = z;

	m[3][0] = m[3][1] = m[3][2] = 0;
	m[3][3] = 1;
}

void RigidBody::getCoordinate(const int rbIndex, const int markerIndex, float (*m)[4], float *c)
{
	float temp[4];
	RB_GetRigidBodyMarker(rbIndex, markerIndex, temp, temp + 1, temp + 2);
	temp[3] = 1;

	float sum;
	for (int i = 0; i < 4; ++i)
	{
		sum = 0;
		for(int j = 0; j < 4; ++j)
		{
			sum += m[i][j] * temp[j];
		}
		c[i] = sum;
	}
}

Vector3 *RigidBody::getPosition(const int index)
{
	if (RB_IsRigidBodyTracked(index))
	{
		float x, y, z, qx, qy, qz, qw, h, a, b;
		RB_GetRigidBodyLocation(index, &x, &y, &z, &qx, &qy, &qz, &qw, &h, &a, &b);
		return new Vector3(x, y, z);
	}
	return NULL;
}
