//Anthony Tyrrell
//Oregon State University CS 551 
//Final Project -> RayTrace engine
//5/21/2016
#include "RayTrace.h"

Camera* mainCamera = nullptr;
Scene* scene = nullptr;

unsigned int nBgColor = CreateColor(33, 185, 3, 255);

Scene* GetNewScene() {
	return new Scene();
}

void CalculateLighting(Camera* pCam, List<Object *> list,Light * light, RayHitInfo &hitInfo, int recursionDepth, bool ambOcc) {
	Vector lightVector;
	if(light->type == DIR_LIGHT) {
		lightVector = -1.0f * light->direction;
	}
	else if (light->type == POINT_LIGHT) {
		lightVector = light->origin - hitInfo.point;
	}
	lightVector.Normalize();

	RayHitInfo info;

	float shadowIntensity = 1.0f;

	Vector surfaceNormal = hitInfo.normal;
	surfaceNormal.Normalize();

	#ifdef ENABLE_SPECULAR_LIGHTING
		Vector cameraVector = pCam->position - hitInfo.point;
		cameraVector.Normalize();

		Vector halfwayVector = lightVector + cameraVector;
		halfwayVector.Normalize();

		float specularIntensity = DotProduct(halfwayVector, surfaceNormal);
		if(specularIntensity < 0.0f) specularIntensity = 0.0f;

		float specularPower = 60.0f;
		specularIntensity = pow(specularIntensity, specularPower);
		
		Color specularColor = light->intensity * specularIntensity * Color(1.0f, 1.0f, 1.0f, 1.0f);
	#else
		Color specularColor = Color(0.0f, 0.0f, 0.0f, 1.0f);
	#endif	
		// Shadows
#ifdef ENABLE_SHADOWS
		Ray rayToLight;
		int numHits = 0;

		rayToLight.origin = hitInfo.point;
		rayToLight.direction = lightVector;
		rayToLight.direction.Normalize();
		if (GetNearestHit(rayToLight, list, info)) {
			hitInfo.pixel = ConvertColor(hitInfo.pHitObject->color * Color(0.01f, 0.01f, 0.01f, 1.0f));
			return;
		}/**/
		shadowIntensity = 1.0f;
#else

#endif

	// DIFFUSE / AMBIENT

	float diffuseIntensity = DotProduct(lightVector, surfaceNormal);
	if(diffuseIntensity < 0.0f) diffuseIntensity = 0.0f;

	Color ambientColor =  Color(0.0f, 0.0f, 0.0f, 1.0f);
	Color diffuseColor = light->intensity * diffuseIntensity * hitInfo.pHitObject->color;

	if(light->type == DIR_LIGHT) {
		shadowIntensity = 1.0f;
		specularColor = Color(0.0f, 0.0f, 0.0f, 1.0f);
	}
	
	Color resultColor = ambientColor + (diffuseColor) + (specularColor);
	
	resultColor = resultColor;
	resultColor = shadowIntensity * resultColor;
	resultColor.Clamp();
	
	hitInfo.pixel += ConvertColor(resultColor);

}

bool RayTrace(FixedOrthographicCamera* pCam, List<Object*> &objList, Light* light, const Ray &ray, RayHitInfo &hitInfo, int recursionDepth) {
	if(recursionDepth > RAY_RECURSSION_DEPTH) return false;

	if(GetNearestHit(ray, objList, hitInfo)) {
		CalculateLighting(pCam, objList, light, hitInfo, recursionDepth + 1);
		return true;
	}
	return false;
}


float RandFloat() {
	//float randNum = ((double) rand() / (RAND_MAX));
	//return ((randNum - 0) / (RAND_MAX - 0));
	return ((double) rand() / (RAND_MAX));
}

int Swizzle(int pixel) {
	// ABGR --> ARGB
	unsigned int r, g, b, a;
	ExtractColor(pixel, r, g, b, a);
	return CreateColor(b, g, r, a);
}

void Swizzle(int* video, int width, int height) {
	for(int n = 0; n < width * height; ++n) {
		video[n] = Swizzle(video[n]);
	}
}