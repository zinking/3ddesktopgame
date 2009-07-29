#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

#include <vector>
#include <cmath>

#include <OgreVector3.h>
using Ogre::Vector3;

#include "optitrack.h"
#include "StereoGraphics.h"
#include "EyesTracking.h"
#include "NPRigidBody.h"



using namespace StereoGraphics;

using std::vector;

#define SCREEN_LEFT -34.4
#define SCREEN_RIGHT 28.8
#define SCREEN_TOP 23.0
#define SCREEN_BOTTOM -27.4

#define CUE_INDEX 0
#define EYE_INDEX 2

#define TRIANGLE_OBSTACLE 1
#define SQUARE_OBSTACLE 3

#define OFFSET_X	0.035
#define OFFSET_Y	0.015
#define OFFSET_Z	-0.015
#define RATIO_X		530
#define RATIO_Y		500
#define RATIO_Z		510

#define CUE_LENGTH	124
#define VELOCITY_THRESHOLD	0.1
#define LOWEST_Y 9
#define TOUCH_DISTANCE	5
