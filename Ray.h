#pragma once

#include "Common.h"

class Ray {
public:
	Ray(Point3 start, Point3 end);
	Ray(Point3 point, Vector3 direction);
	~Ray();
	Point3 GetPoint(float t);
	Point3 GetOrigin();
	Vector3 GetDirection();
private:
	Point3 mOrigin;
	Vector3 mDirction;
};