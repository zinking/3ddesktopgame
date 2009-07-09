
//====================================================================================-----
//== Rigid Body DLL Library
//== Copyright NaturalPoint, Inc.
//==
//== The Rigid Body DLL Library is designed to be a simple yet full featured interface to 
//== the Rigid Body Library.  
//==
//====================================================================================-----

#ifndef NPRIGIDBODY_H
#define NPRIGIDBODY_H

//== Includes ========================================================================-----

//== DLL EXPORT/IMPORT PREPROCESSOR DEFINES ==========================================-----

#ifdef NPRIGIDBODY_EXPORTS
#define RBAPI __declspec(dllexport)
#else
#ifndef STATIC_RB_LINK
#define RBAPI __declspec(dllimport)
#else
#define RBAPI  
#endif
#endif

//== NPRIGIDBODY PUBLIC INTERFACE ===================================================-----

#define NPRESULT int                  //== NPRESULT Defines Call Success/Failure ====-----


//== RIGID BODY STARTUP / SHUTDOWN ==================================================-----

RBAPI   NPRESULT RB_InitializeRigidBody();            //== Initialize Library =======-----
RBAPI   NPRESULT RB_ShutdownRigidBody();              //== Shutdown Library =========-----

//== RIGID BODY INTERFACE ===========================================================-----

RBAPI   NPRESULT RB_LoadProfile(const char *filename); //== Load Calibration Profile =----
RBAPI   NPRESULT RB_StartCameras();                    //== Begin Tracking ===========----
RBAPI   NPRESULT RB_StopCameras();                     //== Stop Tracking ============----
RBAPI   NPRESULT RB_GetNextFrame();                    //== Get Next Available Frame =----
RBAPI   NPRESULT RB_GetLatestFrame();                  //== Get Latest Available Frame ---
RBAPI   NPRESULT RB_LoadDefinition(const char *filename); //== Load Rigid Body Def File --
RBAPI   NPRESULT RB_SaveDefinition(const char *filename); //== Save Rigid Body Def File --

//== RIGID BODY STREAMING ===========================================================-----

RBAPI   NPRESULT RB_StreamTrackd(bool enabled);        //== Start/stop Trackd Stream =----
RBAPI   NPRESULT RB_StreamVRPN(bool enabled, int port);//== Start/stop VRPN Stream ===----
RBAPI   NPRESULT RB_StreamNP    (bool enabled);        //== Start/stop NaturalPoint Stream 

//== RIGID BODY FRAME ===============================================================-----

RBAPI   int      RB_FrameMarkerCount();               //== Returns Frame Markers Count ---
RBAPI   float    RB_FrameMarkerX(int index);          //== Returns X Coord of Marker -----
RBAPI   float    RB_FrameMarkerY(int index);          //== Returns Y Coord of Marker -----
RBAPI   float    RB_FrameMarkerZ(int index);          //== Returns Z Coord of Marker -----

//== RIGID BODY CONTROL =============================================================-----

RBAPI   BOOL     RB_IsRigidBodyTracked(int index);    //== Is rigid body currently vis ---
RBAPI   void     RB_GetRigidBodyLocation(int RigidIndex,   //== Rigid Body Index ======---
                        float *x, float *y, float *z,                  //== Position ==---
                        float *qx, float *qy, float *qz, float *qw,    //== Orientation -- 
                        float *heading, float *attitude, float *bank); //== Orientation --

RBAPI   void     RB_ClearRigidBodyList();             //== Clear all rigid bodies =====---
RBAPI   int      RB_GetRigidBodyCount();              //== Returns number of defined RBs -


RBAPI   void     RB_DeleteRigidBodyMarker(int RigidIndex, int MarkerIndex); //=========---
RBAPI   void     RB_AddRigidBodyMarker(int RigidIndex, float x, float y, float z); //==---
RBAPI   void     RB_SetRigidBodyOrigin(int RigidIndex, float x, float y, float z); //==---

RBAPI   int      RB_GetRigidBodyID(int index);        //== Get Rigid Body ID ==========---
RBAPI   void     RB_SetRigidBodyID(int index,int ID); //== Set Rigid Body ID ==========---

RBAPI   void     RB_CreateRigidBody(const char *name);//== Create Rigid Body ==========---
RBAPI   void     RB_DeleteRigidBody(int index);       //== Delete Rigid Body ==========---

RBAPI   float    RB_GetRigidBodyFlexibility(int index);              //== Get Flex ====---
RBAPI   void     RB_SetRigidBodyFlexibility(int index, float value); //== Set Flex ====---
RBAPI   float    RB_GetRigidBodyRotationConst(int index);  //== Get Rot Constraint ====---
RBAPI   void     RB_SetRigidBodyRotationConst(int index, float value); //== Set Const =---
RBAPI   float    RB_GetRigidBodyTranslationConst(int index); //== Get Translation Const --
RBAPI   void     RB_SetRigidBodyTranslationConst(int index, float value); //== Set Const -

RBAPI   void     RB_SetRigidBodyEnabled(int index, bool enabled);    //== Set Tracking ---
RBAPI   BOOL     RB_GetRigidBodyEnabled(int index);                  //== Get Tracking ---

RBAPI   void     RB_SetRigidBodyColor(int index, int r, int g, int b); //== Set color  ---
RBAPI   int      RB_GetRigidBodyColorR(int index);                     //== Get color  ---
RBAPI   int      RB_GetRigidBodyColorG(int index);                     //== Get color  ---
RBAPI   int      RB_GetRigidBodyColorB(int index);                     //== Get color  ---

RBAPI   int      RB_GetRigidBodyMarkerCount(int index);          //== Get marker count ---
RBAPI   void     RB_GetRigidBodyMarker(int RigidIndex,           //== Get rigid marker ---
                        int MarkerIndex, float *x, float *y, float *z);

RBAPI   int      RB_GetSyncQuality(); //== Returns Sync Quality as follows: --------------
                                      //== 0=No Sync 1=Hardware Sync 2=Good Software Sync
                                      //== 3=Poor Sync

//== POINT CLOUD INTERFACE ==========================================================-----

RBAPI   void     RB_SetPointCloudTrackingParams(int iMinRays, float fMaxResidual,
                        float fMinAngle, float fMinRayLength, float fMaxRayLength);
RBAPI   void     RB_GetPointCloudTrackingParams(int* iMinRays, float* fMaxResidual,
                        float* fMinAngle, float* fMinRayLength, float* fMaxRayLength);

RBAPI   int      RB_CameraCount();                    //== Returns Camera Count =====-----
RBAPI   float    RB_CameraXLocation(int index);       //== Returns Camera's X Coord =-----
RBAPI   float    RB_CameraYLocation(int index);       //== Returns Camera's Y Coord =-----
RBAPI   float    RB_CameraZLocation(int index);       //== Returns Camera's Z Coord =-----
RBAPI   float    RB_CameraOrientationMatrix(int camera, int index); //== Orientation -----

//== RESULT PROCESSING ==============================================================-----

RBAPI   const char *RB_GetResultString(NPRESULT result); //== Return Plain Text Message --

#define NPRESULT_SUCCESS 0                            //== Successful Result ======-------


#endif