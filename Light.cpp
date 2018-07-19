#include "Light.h"
Light::Light()
{
}
Light::Light(RGBColor irradiance) :mIrradiance(irradiance) {

}

Light::~Light()
{
}

AmbientLight::AmbientLight()
{
}

AmbientLight::~AmbientLight()
{
}

AmbientLight::AmbientLight(RGBColor irradiance):Light(irradiance)
{
}

RGBColor AmbientLight::GetIrradiance(Point3 position) const
{
	return mIrradiance;
}

Ray AmbientLight::GetShadowRay(Point3 position) const
{
	return Ray(position,Vector3());
}

Vector3 AmbientLight::GetDirection(Point3 position) const
{
	return Vector3();
}

DirectedLight::DirectedLight()
{
}

DirectedLight::~DirectedLight()
{
}

DirectedLight::DirectedLight(RGBColor irradiance, Vector3 diretion):Light(irradiance),
							mDiretion(diretion)
{
}

RGBColor DirectedLight::GetIrradiance(Point3 position) const
{
	return mIrradiance;
}

Ray DirectedLight::GetShadowRay(Point3 position) const
{
	return Ray(position,mDiretion);
}

Vector3 DirectedLight::GetDirection(Point3 position) const
{
	return mDiretion;
}
