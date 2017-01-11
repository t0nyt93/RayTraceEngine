//Anthony Tyrrell
//Oregon State University CS 551 
//Final Project -> RayTrace engine
//5/21/2016
//scene.h
#pragma once

#include "myList.h"


class Object;
class Light;

class Scene {
	public:
		List<Object*> objects;
		List<Light*> lights;
};