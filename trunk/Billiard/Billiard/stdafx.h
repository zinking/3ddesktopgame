#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <vector>

#include <OgreVector3.h>
using Ogre::Vector3;

#include "optitrack.h"
#include "StereoGraphics.h"
#include "EyesTracking.h"
#include "NPRigidBody.h"



using namespace StereoGraphics;

using std::vector;

#define SCREEN_LEFT -33.5
#define SCREEN_RIGHT 33.5
#define SCREEN_TOP 25.3
#define SCREEN_BOTTOM -25.3

#define CUE_INDEX 0

#define EYE_INDEX 2

#define TRIANGLE_OBSTACLE 1
#define SQUARE_OBSTACLE 3

#define OFFSET_X	0.035
#define OFFSET_Y	0.015
#define OFFSET_Z	0.01
#define RATIO_X		530
#define RATIO_Y		500
#define RATIO_Z		500

#define CUE_LENGTH	124
#define VELOCITY_THRESHOLD	0.1
#define LOWEST_Y 9
#define TOUCH_DISTANCE	5
