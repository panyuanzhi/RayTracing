#pragma once

#include <iostream>
#include "Camera.h"
int main() {
	std::cout << "RayTracing Start" << std::endl;
	Camera camera(10, 20, 20, 512, 512);
	Point3 center;
	center[0] = -10; center[1] = 5; center[2] = 20;
	Sphere sphere1(center, 5);
	RGBColor ka(0.2, 0.2, 0.2, 0.0);
	RGBColor kd(0.4, 0.0, 0.0, 0.0);
	RGBColor ks(0.4, 0.0, 0.0, 0.0);
	sphere1.ka = ka; sphere1.kd = kd; sphere1.ks = ks;

	center[0] = 10; center[1] = 5; center[2] = 20;
	Sphere sphere2(center, 5);
	kd = RGBColor(0.0, 0.4, 0.0, 0.0);
	ks = RGBColor(0.0, 0.4, 0.0, 0.0);
	sphere2.ka = ka; sphere2.kd = kd; sphere2.ks = ks;

	AmbientLight ambient(RGBColor(0.5, 0.5, 0.5, 0.0));
	Vector3 direction;
	direction[0] = 0; direction[1] = 0; direction[1] = 1;
	DirectedLight dirLight(RGBColor(0.8, 0.8, 0.8, 0.0), direction);

	Scene scene;
	scene.mObjects.push_back(&sphere1);
	scene.mObjects.push_back(&sphere2);
	scene.mDirLight = dirLight;

	camera.Render(scene);

	std::cout << "RayTracing End" << std::endl;
	return 0;
}