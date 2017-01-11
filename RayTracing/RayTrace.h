//Anthony Tyrrell
//Oregon State University CS 551 
//Final Project -> RayTrace engine
//5/21/2016

#pragma once

#include "camera.h"
#include "scene.h"
#include "myList.h"
//#include <math>

#define RAY_RECURSSION_OFFSET 9

#define RAY_RECURSSION_DEPTH 10
#define NUM_SHADOW_RAYS 8 //128 //512 //16 //8 //256 //1024 //32
#define MAX_AMB_OCC_LENGTH 200.0f //400.0f //800.0f
#define MAX_ABM_OCC_WINDOW 20

// FEATURES /////////////////////////////////////////////////////////////////////////

// Screen Resolution
#define VGA
#define ENABLE_SPECULAR_LIGHTING

#define ENABLE_SHADOWS

// Camera Type
#define USE_ORTHO_CAMERA
//#define USE_PERSP_CAMERA
//#define USE_PERSP_LOOK_AT




extern Camera* mainCamera;
extern Scene* scene;

extern unsigned int nBgColor;

Scene* GetNewScene();

void CalculateLighting(Camera* pCam,List<Object *>, Light* light, RayHitInfo &hitInfo, int recursionDepth, bool ambOcc = false);

bool RayTrace(FixedOrthographicCamera* pCam, List<Object*> &objList, Light* light, const Ray &ray, RayHitInfo &hitInfo, int recursionDepth);

float RandFloat();
int Swizzle(int pixel);
void Swizzle(int* video, int width, int height);
