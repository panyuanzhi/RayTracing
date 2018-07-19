#pragma once

#include "Scene.h"
class Camera {
public:
	Camera(float focalLength, float imageWidth, float imageHeight, int resolutionX, int resolutionY);
	~Camera();
	void Render(const Scene &scene);
	void SetBounce(int bounce);
private:
	RGBColor RayTracing(Ray ray, const Scene &scene, int bounce);
	RGBColor BlinPhong(const Object &object, Point3 position, Vector3 viewDir, const Light &light);
	void DrawPixel(int x, int y, RGBColor color);
	void InitColorBuffer();
	void WriteColorBuffer();
private:
	//默认原点作为相机的位置
	Point3 mEye;
	float mFocalLength;
	float mImageWidth;
	float mImageHeight;
	int mResolutionX;
	int mResolutionY;
	int mBounce;
	ImageType::Pointer mColorBuffer;
};