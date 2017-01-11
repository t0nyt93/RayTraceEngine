// Student.Ray.h
///////////////////////////////////////////////////////////////////////////////////////////////
#pragma once


#include "sphere.h"
#include "color.h"
#include "myMath.h"
#include "myList.h"
#include "lighting.h"
#include "scene.h"

#include <math.h>

class Object;
class SphereObject;

class Ray {
	public:
		Point origin;
		Vector direction;
		
		Ray();
		Point GetPointAt(float t) const;
};

class BaryCoord {
	public:
		float alpha, beta, gamma;
		float Calculate(float a, float b, float c) const;
};


class HitInfo {
	public:
		float t;
		Point point;
		Ray ray;
		Vector normal;
};


class RayHitInfo {
	public:
		float t, tu, tv;
		Ray ray;
		Point point;
		unsigned int pixel;
		Vector normal;
		Vector tangent;
		Vector reflection;
		Vector refraction;
		Object* pHitObject;
		BaryCoord baryCoord;
		RayHitInfo();
};

bool GetNearestHit(const Ray &ray, List<Object*> &objList, RayHitInfo &hitInfo);
