#pragma once
#include "RGBColor.h"
#include "Ray.h"
class Light {
public:
	Light();
	Light(RGBColor irradiance);
	virtual ~Light();
	virtual RGBColor GetIrradiance(Point3 position) const = 0 ;
	virtual Ray GetShadowRay(Point3 position) const = 0;
	virtual Vector3 GetDirection(Point3 position) const = 0;
protected:
	RGBColor mIrradiance;
};

class AmbientLight :public Light {
public:
	AmbientLight();
	~AmbientLight();
	AmbientLight(RGBColor irradiance);
	virtual RGBColor GetIrradiance(Point3 position) const;
private:
	virtual Ray GetShadowRay(Point3 position) const ;
	virtual Vector3 GetDirection(Point3 position) const;
};

class DirectedLight :public Light {
public:
	DirectedLight();
	~DirectedLight();
	DirectedLight(RGBColor irradiance, Vector3 diretion);
	virtual RGBColor GetIrradiance(Point3 position) const;
	virtual Ray GetShadowRay(Point3 position) const;
	virtual Vector3 GetDirection(Point3 position) const;
private:
	Vector3 mDiretion;
};

