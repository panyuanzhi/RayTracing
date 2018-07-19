#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

Object * Scene::Hit(Ray ray, Point3 & postion) const
{
	float t = std::numeric_limits<float>::max();
	bool hit = false;
	Object* object = nullptr;
	Objects::const_iterator it = mObjects.begin();
	Objects::const_iterator end = mObjects.end();
	for (; it != end; ++it) {
		float ttmp = (*it)->Hit(ray);
		if (ttmp > 0 && ttmp < t) {
			hit = true;
			object = *it;
			t = ttmp;
		}
	}
	if (hit) {
		postion = ray.GetPoint(t);
		return object;
	}
	else return nullptr;
}
