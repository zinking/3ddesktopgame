#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "stdafx.h"

class RigidBody {
public:
	RigidBody(const int index);
	vector<Vector3> &track();
	int getVertexCount() const;
	static void getTransformMatrix(const int index, float (*m)[4]);
	static void getCoordinate(const int rbIndex, const int markerIndex, float (*m)[4], float *);
	static Vector3 *getPosition(const int index);
private:
	vector<Vector3> vertices;
	int rbIndex;
};

#endif