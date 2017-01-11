//Anthony Tyrrell
//Oregon State University CS 419
//Final term project - Ray Trace engine
#include "ray.h"

Ray::Ray() {

}

RayHitInfo::RayHitInfo() {
	this->pixel = 0x00000000;
	this->t = 0;
	this->tu = 0;
	this->tv = 0;
	this->normal = Vector();
	this->tangent = Vector();
	this->reflection = Vector();
	this->refraction = Vector();
	this->baryCoord = BaryCoord();
	this->pHitObject = nullptr;
	this->ray = Ray();	
	this->point = Point();
	
}

Point Ray::GetPointAt(float t) const {
	Point result;

	result.x = origin.x + t * direction.x;
	result.y = origin.y + t * direction.y;
	result.z = origin.z + t * direction.z;
	result.w = origin.w + t * direction.w;

	return result;
}

float BaryCoord::Calculate(float a, float b, float c) const{
	return this->alpha * a + this->beta * b + this->gamma * c;
}

bool GetNearestHit(const Ray &ray, Object &obj, RayHitInfo &hitInfo) {
	RayHitInfo nearestHit;
	nearestHit.t = 99999.0f;
	bool bHit = false;

	RayHitInfo h;
	if(obj.DoesRayHitYou(ray, h)) {
		if(h.t < nearestHit.t) {
			nearestHit = h;
			bHit = true;
		}
	}
	hitInfo = nearestHit;
	return bHit;
}


bool GetNearestHit(const Ray &ray, List<Object*> &objList, RayHitInfo &hitInfo) {
	RayHitInfo nearestHit;
	nearestHit.t = 99999.0f;
	bool bHit = false;

	for(int n = 0; n < objList.length; ++n) {
		Object* obj = objList[n];
		RayHitInfo info;
		if(obj->DoesRayHitYou(ray, info)) {
			if(info.t < nearestHit.t) {
				nearestHit = info;
				bHit = true;
			}
		}
	}
	hitInfo = nearestHit;
	return bHit;
}

