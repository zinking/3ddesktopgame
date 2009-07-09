#ifndef EYESTRACKING_HEADER
#define EYESTRACKING_HEADER

namespace EyesTracking
{
	void Initialize(const char* calibFile, const char* glassDef);
	void Terminate();
	bool GetEyesPosition(double& leftx, double& lefty, double& leftz, double& rightx, double& righty, double& rightz);
};

#endif