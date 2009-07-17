#ifndef STEREO_GRAPHICS_HEADER
#define STEREO_GRAPHICS_HEADER

#include <iostream>
//#include <gl/glut.h>

namespace StereoGraphics
{	
	//Please note that no modification of projection matrix is allowed between BeginMonoDraw()
	//and EndMonoDraw(), BeginStereoDraw() and EndStereoDraw()
	void SetProjectorViewport(double left, double right, double bottom, double top);
	void SetNearClipDistance(double aNear);
	void EyeLookFrom(double eyex, double eyey, double eyez);
	void BeginMonoDraw(int eye);
	void EndMonoDraw();	
	void SetLeftEyePosition(double eyex, double eyey, double eyez);
	void SetRightEyePosition(double eyex, double eyey, double eyez);	
	void BeginStereoDraw();	
	void EndStereoDraw();	
	void EndStereoDraw(double aLeftEyeX, double aLeftEyeY, double aLeftEyeZ, double aRightEyeX, double aRightEyeY, double aRightEyeZ);
}
#endif