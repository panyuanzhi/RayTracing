#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

Sphere::Sphere(Point3 center, float radius)
{
	mCenter = center;
	mRadius = radius;
}

Sphere::~Sphere()
{
}

float Sphere::Hit(Ray ray)
{
	//(d · d)t2 + 2d · (e − c)t + (e − c) · (e − c) − R2 = 0.
	Vector3 d = ray.GetDirection();
	Point3 e = ray.GetOrigin();
	float A = d*d;
	float B = 2 * (d*(e - mCenter));
	float C = (e - mCenter).GetSquaredNorm() - mRadius*mRadius;
	float delta = B*B - 4 * A*C;
	if (delta >= 0)
		return (-B - sqrt(delta)) / 2 * A;
	else return -1;
}

Vector3 Sphere::GetNormal(Point3 position) const
{
	Vector3 normal = position - mCenter;
	normal.Normalize();
	return normal;
}

Plane::Plane(Point3 point, Vector3 normal) {
	mPoint = point;
	mNormal = normal.Normalize();
}
Plane::~Plane()
{
}

float Plane::Hit(Ray ray)
{
	//t =((p− e) · n)/(d · n)
	float ddotn = ray.GetDirection()*mNormal;
	if (ddotn != 0) {
		return ((mPoint - ray.GetOrigin())*mNormal) / ddotn;
	}
	else {
		//点积为0，说明光线与平面平行，有无穷交点或者没有交点。
		//此处均返回一个负值，当作没有交点处理
		return -1;
	}
}

Vector3 Plane::GetNormal(Point3 position) const
{
	return mNormal;
}
