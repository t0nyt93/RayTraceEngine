//Anthony Tyrrell
//Oregon State University CS 551 
//Final Project -> RayTrace engine
//5/21/2016
//sphere.cpp is used to store information about types of objects, as far as this project is concerned it concerns spheres.
#include "sphere.h"
#include "myMath.h"
#include <math.h>

Object::Object() {
	this->color = COLOR::Color( 0.9f, 0.2f, 0.85f, 1.0f);
	this->reflectivity = 1.0f;
}

Object::~Object() {
	//delete this->texture;
}

SphereObject::SphereObject(Point pos) {
	this->position = pos;
	this->radius = _DEFAULT_RADIUS;
}
SphereObject::SphereObject() {
	this->position = Point();
	this->radius = _DEFAULT_RADIUS;
}

SphereObject::SphereObject(SphereObject* sphere) {
	this->color = sphere->color;
	this->position = sphere->position;
	this->radius = sphere->radius;
}

bool SphereObject::DoesRayHitYou(const Ray &ray, RayHitInfo &hitInfo) {
	// Prep variables for the equation:
	// d = b*b - 4.0 * a * c
	//////////////////////////////////////////////////////////////////////
	float a = DotProduct(ray.direction, ray.direction);
	
	// Holds the vector from the objects position to the ray's origin, 
	// then will hold the result of a dot product
	Vector p;	

	p = ray.origin - this->position;
	p = 2.0f * p;
	float b = DotProduct(p, ray.direction);

	p = ray.origin - this->position;
	float c = DotProduct(p, p) - this->radius * this->radius;
	
	// d = b*b - 4.0 * a * c
	float d = (float)(b * b - 4.0 * a * c);
	//////////////////////////////////////////////////////////////////////

	// Escape early
	if ( d < 0.0) return false;

	float e = sqrt(d);

	float t1 = (-b - e) / (2 * a);
	float t2 = (-b + e) / (2 * a);
	
	// t greaters greater than 0.0
	if(t1 < 0.0f) t1 = 0.0f;
	if(t2 < 0.0f) t2 = 0.0f;
	
	// Take the nearest of the two
	float t = (t1 < t2) ? t1 : t2;
	if( t <= 0.001f) return false;

	hitInfo.t = t;
	hitInfo.point = ray.GetPointAt(t);
	hitInfo.pHitObject = this;
	hitInfo.ray = ray;
	hitInfo.normal = hitInfo.point - this->position;
	hitInfo.normal.Normalize();
	hitInfo.tu = (hitInfo.normal.x / 2.0f) + 0.5f;
	hitInfo.tv = (hitInfo.normal.y / 2.0f) + 0.5f;
	return true;
}

TriangleObject::TriangleObject() {
	this->a = Point(-325.0f, 0.0f, 200.0f, 0.0f);
	this->b = Point(-300.0f, 200.0f, 200.0f, 0.0f);
	this->c = Point(-275.0f, 0.0f, 200.0f, 0.0f);

	this->CalculateNormal();
}

TriangleObject::TriangleObject(Point a, Point b, Point c) {
	this->a = a;
	this->b = b;
	this->c = c;

	this->CalculateNormal();
}

TriangleObject::TriangleObject(TriangleObject* tri) {
	this->a = tri->a;
	this->b = tri->b;
	this->c = tri->c;

	this->color = tri->color;
}

bool TriangleObject::DoesRayHitYou(const Ray & ray, RayHitInfo &hitInfo) {
	// Using the CLOCKWISE WINDING routine

	// Info for the triangles X values
	double a = this->a.x - this->b.x, b = this->a.x - this->c.x, c = ray.direction.x, d = this->a.x - ray.origin.x;
	// Info for the triangles Y values
	double e = this->a.y - this->b.y, f = this->a.y - this->c.y, g = ray.direction.y, h = this->a.y - ray.origin.y;
	// Info for the triangles Z values
	double i = this->a.z - this->b.z, j = this->a.z - this->c.z, k = ray.direction.z, l = this->a.z - ray.origin.z;

	// Complicataed Triangle mathematics
	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e *j - f * i;

	double inverse_denom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * inverse_denom;

	if (beta < 0.0) return false;

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inverse_denom;

	if (gamma < 0.0) return false;
	if (beta + gamma > 1.0) return false;

	double e3 = a * p - b * r + d * s;
	double t = e3 * inverse_denom;

	if (t < 0.01f) return false;

	hitInfo.t = (float)t;
	hitInfo.point = ray.GetPointAt((float)(t));
	hitInfo.pHitObject = this;
	hitInfo.ray = ray;
	hitInfo.normal = this->normal;
	hitInfo.baryCoord.alpha = 1.0f - beta - gamma;
	hitInfo.baryCoord.beta = beta;
	hitInfo.baryCoord.gamma = gamma;

	return true;
}

void TriangleObject::CalculateNormal() {
	this->normal = CrossProduct((this->b - this->a), (this->c - this->a));
	this->normal.Normalize();
}