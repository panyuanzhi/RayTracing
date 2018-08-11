#include "Camera.h"
#include "itkImageFileWriter.h"
Camera::Camera( float focalLength, float imageWidth, float imageHeight, int resolutionX, int resolutionY)
{
	mFocalLength = focalLength;
	mImageWidth = imageWidth;
	mImageHeight = imageHeight;
	mResolutionX = resolutionX;
	mResolutionY = resolutionY;
	mBounce = 4;
	InitColorBuffer();
	mEye[0] = 0; mEye[1] = 0; mEye[2] = 0;
}

Camera::~Camera()
{
}

void Camera::Render(const Scene &scene)
{
	float deltaX = mImageWidth / (float)mResolutionX;
	float deltaY = mImageHeight / (float)mResolutionY;
	float halfHeight = mImageHeight / 2.0;
	float halfWidth = mImageWidth / 2.0;
	//从左上角开始
	int indexX = 0, indexY = 0;
	for (float y = halfHeight - deltaY / 2.0; y > -halfHeight; y -= deltaY,++indexY) {
		indexX = 0;
		for (float x = -halfWidth + deltaX / 2.0; x < halfWidth; x += deltaX, ++indexX) {
			Point3 sample;
			sample[0] = x; sample[1] = y; sample[2] = mFocalLength;
			Ray ray(mEye, sample);
			RGBColor color = RayTracing(ray, scene, mBounce);
			DrawPixel(indexX, indexY, color);
		}
	}

	WriteColorBuffer();
}

void Camera::SetBounce(int bounce)
{
	mBounce = bounce;
}

RGBColor Camera::RayTracing(Ray ray, const Scene & scene, int bounce)
{
	if (bounce <= 0)
		return RGBColor();
	Point3 position;
	Object* object = scene.Hit(ray, position);	
	if (object) {
		//先计算环境光分量，
		RGBColor color = object->ka*scene.mAmbient.GetIrradiance(position);
		//暂时先写单光源情况
		{
			Ray ray = scene.mDirLight.GetShadowRay(position);
			//由于数值精度问题，求解的交点不一定精确的在物体表面上，会有一定的偏离。
			//有可能会在在物体内部，或在物体外部，因此对阴影光线沿射线方向做一定的便偏移。
			float epsilon = 0.001;
			Point3 point =  ray.GetPoint(epsilon);
			Ray shadowRay(point, ray.GetDirection());
			Point3 shadowPoint;
			Object *shadowObject = scene.Hit(shadowRay,shadowPoint);
			if (shadowObject) {
				return color;
			}
			else {
				Vector3 viewDir = mEye - position;
				Vector3 lightDir = scene.mDirLight.GetDirection(position);
				Vector3 l;
				l[0] = -lightDir[0]; l[1] = -lightDir[1]; l[2] = -lightDir[2];
				color = color + BlinPhong(*object, position, viewDir, l, scene.mDirLight.GetIrradiance(position));
				return color;
			}
		}
	}
	else {
		return RGBColor(0.0,0.0,0.0,0.0);
	}
	
}

RGBColor Camera::BlinPhong(const Object & object, Point3 position, Vector3 viewDir, Vector3 l, RGBColor irradiance)
{
	Vector3 half = (l + viewDir).Normalize();
	Vector3 normal = object.GetNormal(position);
	RGBColor kd = object.kd;
	RGBColor diffuse = (kd*irradiance)*std::max(0.0f, l*normal);
	RGBColor ks = object.ks;
	//高光指数
	float p = 2.0;
	RGBColor specular = (ks*irradiance)*powf(std::max(normal*half,0.0f) , p);
	return diffuse+specular;
}

void Camera::DrawPixel(int x, int y, RGBColor color)
{
	ImageType::IndexType pixelIndex = { x,y };
	color.saturate();
	ImagePixelType pixel;
	pixel[0] = itk::NumericTraits<ImagePixelType::ValueType>::max()*color[0];
	pixel[1] = itk::NumericTraits<ImagePixelType::ValueType>::max()*color[1];
	pixel[2] = itk::NumericTraits<ImagePixelType::ValueType>::max()*color[2];

	mColorBuffer->SetPixel(pixelIndex, pixel);
}

void Camera::InitColorBuffer()
{
	mColorBuffer = ImageType::New();
	ImageType::IndexType start;
	start[0] = 0;
	start[1] = 0;
	ImageType::SizeType size;
	size[0] = mResolutionX;
	size[1] = mResolutionY;
	ImageType::RegionType region;
	region.SetSize(size);
	region.SetIndex(start);
	mColorBuffer->SetRegions(region);
	mColorBuffer->Allocate(true);
}

void Camera::WriteColorBuffer()
{
	typedef itk::ImageFileWriter< ImageType > WriterType;
	WriterType::Pointer writer = WriterType::New();
	writer->SetFileName("RayTracing.png");
	writer->SetInput(mColorBuffer);
	try
	{
		writer->Update();
	}
	catch (itk::ExceptionObject & error)
	{
		std::cerr << "Error: " << error << std::endl;
	}
}
