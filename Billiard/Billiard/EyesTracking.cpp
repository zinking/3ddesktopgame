#include "stdafx.h"
#include <windows.h>
#include <math.h>
//#include <NPPointCloud.h>
#include "NPRigidBody.h"
#include "EyesTracking.h"

void CheckResult(NPRESULT result)   //== CheckResult function will display errors and ---
//== exit application after a key is pressed =====---
{
	if(result==NPRESULT_SUCCESS)    //== If there is no error, do nothing ============---
		return;

	//printf("Error: %s\n\n(Press any key to continue)\n",NP_GetResultString(result));

	getchar();

	//exit(1);
}

void EyesTracking::Initialize(const char* calibFile, const char* glassDef)
{
	RB_InitializeRigidBody();
	CheckResult(RB_LoadProfile(calibFile));
	CheckResult(RB_LoadDefinition(glassDef));
	CheckResult(RB_StartCameras());
}

void EyesTracking::Terminate()
{
	RB_StopCameras();
	RB_ShutdownRigidBody();
}

bool EyesTracking::GetEyesPosition(double& leftx, double& lefty, double& leftz, double& rightx, double& righty, double& rightz)
{
	//CheckResult(RB_GetLatestFrame());
	static float lastlx, lastly, lastlz, lastrx, lastry, lastrz;
	if (RB_GetLatestFrame()==NPRESULT_SUCCESS)
	{
		if (RB_IsRigidBodyTracked(0))
		{
// 		float cx,cy,cz,q0,q1,q2;
// 		float x1, x2, y1, y2, z1, z2;
// 		float t0, t1, t2, t3;
// 
// 		RB_GetRigidBodyLocation(0, &cx, &cy, &cz,  &q0, &q1, &q2, &t0, &t1, &t2, &t3);
// 		/*RB_GetRigidBodyMarker(0, 0, &x1, &y1, &z1);
// 		RB_GetRigidBodyMarker(0, 1, &x2, &y2, &z2);
// 		leftx=(x1+x2)/2.0; leftz=(y1+y2)/2.0; lefty=(z1+z2)/2.0;
// 		RB_GetRigidBodyMarker(0, 2, &x1, &y1, &z1);
// 		RB_GetRigidBodyMarker(0, 3, &x2, &y2, &z2);
// 		rightx=(x1+x2)/2.0; rightz=(y1+y2)/2.0; righty=(z1+z2)/2.0;*/
// 		
// 		leftx=rightx=cx;
// 		lefty=righty=cz;
// 		leftz=rightz=cy;
// 
// 
// 		fprintf(stderr,"\nleft: (%f, %f, %f), right: (%f, %f, %f)",leftx,lefty,leftz,rightx,righty,rightz);
// 		return true;
		float x,y,z,qx,qy,qz,qw,heading,attitude,bank;
		RB_GetRigidBodyLocation(0,&x,&y,&z,&qx,&qy,&qz,&qw,&heading,&attitude,&bank);

		float m[4][4];
		float xx,xy,xz,xw,yy,yz,yw,zz,zw;
		xx=qx*qx; xy=qx*qy; xz=qx*qz; xw=qx*qw;

		yy=qy*qy; yz=qy*qz; yw=qy*qw; zz=qz*qz; zw=qz*qw;

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
		RB_GetRigidBodyMarker(0,0,&left[0],&left[1],&left[2]);
		left[3]=1;

		float right[4];
		RB_GetRigidBodyMarker(0,1,&right[0],&right[1],&right[2]);
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
		}  //nleft[3]=nright[3]=1

		leftx=nleft[0]+(nright[0]-nleft[0])/3;
		leftz=nleft[1]+(nright[1]-nleft[1])/3;
		lefty=nleft[2]+(nright[2]-nleft[2])/3;

		rightx=nleft[0]+(nright[0]-nleft[0])*2/3;
		rightz=nleft[1]+(nright[1]-nleft[1])*2/3;
		righty=nleft[2]+(nright[2]-nleft[2])*2/3;
		
		lastlx=leftx; lastly=lefty; lastlz=leftz;
		lastrx=rightx; lastry=righty; lastrz=rightz;

		//fprintf(stderr,"\nrigid: (%f, %f, %f)",x,y,z);
		//fprintf(stderr,"\nleft: (%f, %f, %f), right: (%f, %f, %f)",leftx,lefty,leftz,rightx,righty,rightz);
		return true;
		}
		else fprintf(stderr,"\nnot tracked");
	}
	else
	{
		fprintf(stderr,"\nWaiting to get frame ready...");
	}
	leftx=lastlx; lefty=lastly; leftz=lastlz;
	rightx=lastrx; righty=lastry; rightz=lastrz;
	return false;
}