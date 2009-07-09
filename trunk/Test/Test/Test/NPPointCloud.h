
//====================================================================================-----
//== Point Cloud DLL Library
//== Copyright NaturalPoint, Inc.
//==
//== The Point Cloud DLL Library is designed to be a simiplified non-COM interface to 
//== the Point Cloud Library.  This should allow developers a quick and easy way to 
//== get access to the Point Cloud Library without all the overhead of using COM.
//==
//====================================================================================-----

#ifndef NPPOINTCLOUD_H
#define NPPOINTCLOUD_H

//== Includes ========================================================================-----

//== DLL EXPORT/IMPORT PREPROCESSOR DEFINES ==========================================-----

#ifdef NPPOINTCLOUD_EXPORTS
#define NPAPI __declspec(dllexport)
#else
#ifndef STATIC_LINK
#define NPAPI __declspec(dllimport)
#else
#define NPAPI  
#endif
#endif

//== NPPOINTCLOUD PUBLIC INTERFACE ==================================================-----

#define NPRESULT int                  //== NPRESULT Defines Call Success/Failure ====-----

//== POINT CLOUD STARTUP / SHUTDOWN =================================================-----

NPAPI   NPRESULT NP_InitializePointCloud();            //== Initialize Library ======-----
NPAPI   NPRESULT NP_ShutdownPointCloud();              //== Shutdown Library ========-----

//== POINT CLOUD INTERFACE ==========================================================-----

NPAPI   NPRESULT NP_LoadProfile(const char *filename); //== Load Calibration Profile =----
NPAPI   NPRESULT NP_Start();                           //== Start Point Cloud Capture ----
NPAPI   NPRESULT NP_Stop();                            //== Stop  Point Cloud Capture ----
NPAPI   NPRESULT NP_GetNextFrame();                    //== Get Next Available Frame =----
NPAPI   NPRESULT NP_GetLatestFrame();                  //== Get Latest Available Frame ---

//== POINT CLOUD FRAME INTERFRACE ===================================================-----

NPAPI   int      NP_FrameMarkerCount();               //== Returns Frame Markers Count ---
NPAPI   float    NP_FrameMarkerX(int index);          //== Returns X Coord of Marker -----
NPAPI   float    NP_FrameMarkerY(int index);          //== Returns Y Coord of Marker -----
NPAPI   float    NP_FrameMarkerZ(int index);          //== Returns Z Coord of Marker -----

//== POINT CLOUD CAMERA INTERFACE ===================================================-----

NPAPI   int      NP_CameraCount();                    //== Returns Camera Count =====-----
NPAPI   float    NP_CameraXLocation(int index);       //== Returns Camera's X Coord =-----
NPAPI   float    NP_CameraYLocation(int index);       //== Returns Camera's Y Coord =-----
NPAPI   float    NP_CameraZLocation(int index);       //== Returns Camera's Z Coord =-----
NPAPI   float    NP_CameraOrientationMatrix(int camera, int index); //== Orientation -----

//== POINT CLOUD TRACKING PARAMETERS ================================================-----

NPAPI   float    NP_GetMaximumResidual();
NPAPI   void     NP_SetMaximumResidual(float residual);
  
NPAPI   int      NP_GetMinimumRayCount();
NPAPI   void     NP_SetMinimumRayCount(int rays);
  
NPAPI   float    NP_GetMinimumAngle();
NPAPI   void     NP_SetMinimumAngle(float angle);
  
NPAPI   float    NP_GetMinimumRayLength();
NPAPI   void     NP_SetMinimumRayLength(float length);
  
NPAPI   float    NP_GetMaximumRayLength();
NPAPI   void     NP_SetMaximumRayLength(float length);

NPAPI   int      NP_GetSynchronizationQuality();
NPAPI   double   NP_GetTriangulationTime();

//== POINT CLOUD RESULT PROCESSING ==================================================-----

NPAPI   const char *NP_GetResultString(NPRESULT result); //== Return Plain Text Message --

#define NPRESULT_SUCCESS 0                            //== Successful Result ======-------

//=================================================================================-------

#endif
