#pragma once

#include "Ray.h"
#include <vector>
#include "RGBColor.h"
class Object {
public:
	Object();
	virtual ~Object();
	virtual float Hit(Ray ray) = 0;
	virtual Vector3 GetNormal(Point3 position) const =0;
public:
	//²ÄÖÊÏµÊý
	RGBColor ka;
	RGBColor kd;
	RGBColor ks;
};

class Sphere :public Object{
public:
	Sphere(Point3 center, float radius);
	~Sphere();
	virtual float Hit(Ray ray);
	virtual Vector3 GetNormal(Point3 position) const;
private:
	Point3 mCenter;
	float mRadius;
};
class Plane :public Object {
	Plane(Point3 point, Vector3 normal);
	~Plane();
	virtual float Hit(Ray ray);
	virtual Vector3 GetNormal(Point3 position) const;
private:
	Point3 mPoint;
	Vector3 mNormal;
};

typedef typename std::vector<Object *> Objects;