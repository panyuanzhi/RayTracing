#include "Ray.h"

Ray::Ray(Point3 start, Point3 end)
{
	mOrigin = start;
	mDirction = end - start;
	mDirction.Normalize();
}

Ray::Ray(Point3 point, Vector3 direction)
{
	mOrigin = point;
	direction.Normalize();
	mDirction = direction;
}

Ray::~Ray()
{
}

Point3 Ray::GetPoint(float t)
{
	return mOrigin + t*mDirction;
}

Point3 Ray::GetOrigin()
{
	return mOrigin;
}

Vector3 Ray::GetDirection()
{
	return mDirction;
}
