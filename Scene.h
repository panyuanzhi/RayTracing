#pragma once
#include "Object.h"
#include "Light.h"
class Scene {
public:
	Scene();
	~Scene();
	Object* Hit(Ray ray, Point3 &postion) const;
public:
	Objects mObjects;
	AmbientLight mAmbient;
	DirectedLight mDirLight;
};