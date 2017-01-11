//Anthony Tyrrell
//Oregon State University CS 551 
//Final Project -> RayTrace engine
//5/21/2016

#pragma once

#include "ray.h"
#include "myMath.h"
#include "color.h"
#include "lighting.h"

class Ray;
class HitInfo;
class RayHitInfo;

#define _DEFAULT_RADIUS 200.0f

class Object {
	public:
		COLOR::Color color;
		float reflectivity;

		Object();
		~Object();
		virtual bool DoesRayHitYou(const Ray &ray, RayHitInfo &hitInfo) = 0;
		//bool DoesRayHitYou(const Ray &ray, RayHitInfo &hitInfo);
};


class SphereObject : public Object {
	public:
		Point position;
		float radius;

		SphereObject();
		SphereObject(Point pos);
		SphereObject(SphereObject* sphere);

		bool DoesRayHitYou(const Ray &ray, RayHitInfo &hitInfo);
};

class TriangleObject : public Object {
public:
	Point a, b, c;
	Vector normal;

	TriangleObject();
	TriangleObject(Point a, Point b, Point c);
	TriangleObject(TriangleObject* tri);

	bool DoesRayHitYou(const Ray & ray, RayHitInfo &hitInfo);
	void CalculateNormal();
};


