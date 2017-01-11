// Student.Camera.h
///////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ray.h"
#include "lighting.h"

#define _FOCAL_LENGTH_DEFAULT 999.0f

class Orientation {
	public:
		Vector right, up, forward;

		void Normalize();
};

class Camera {
	public:
		Point position;
		Vector direction;
		Orientation orientation;

		Ray ray;

		virtual void Initialize();
		virtual Ray GetRay(float x, float y) = 0;
};

class FixedOrthographicCamera : public Camera {
	public:
		void Initialize();
		Ray GetRay(float x, float y);
};

class FixedPerspectiveCamera : public Camera {
	public:
		Point viewportCenter;
		Point focalPoint;

		float focalLength;

		void Initialize();
		Ray GetRay(float x, float y);
		void SetFocalPoint(float f);
		void LookAt(double x, double y, double z);
};

typedef FixedOrthographicCamera FIXED_ORTHO_CAMERA;
typedef FixedPerspectiveCamera FIXED_PERSP_CAMERA;