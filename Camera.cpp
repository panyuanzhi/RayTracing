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
	//�����Ͻǿ�ʼ
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
		//�ȼ��㻷���������
		RGBColor color = object->ka*scene.mAmbient.GetIrradiance(position);
		//��ʱ��д����Դ���
		{
			Ray shadowRay = scene.mDirLight.GetShadowRay(position);
			Point3 shadowPoint;
			Object *shadowObject = scene.Hit(shadowRay,shadowPoint);
			if (shadowObject) {
				return color;
			}
			else {
				color = color + BlinPhong(*object, position, ray.GetDirection(), scene.mDirLight);
				return color;
			}
		}
	}
	else {
		return RGBColor(0.0,0.0,0.0,0.0);
	}
	
}

RGBColor Camera::BlinPhong(const Object & object, Point3 position, Vector3 viewDir, const Light & light)
{
	Vector3 l = light.GetDirection(position);
	Vector3 half = (l + viewDir).Normalize();
	Vector3 normal = object.GetNormal(position);
	RGBColor irradiance = light.GetIrradiance(position);
	RGBColor kd = object.kd;
	RGBColor diffuse = (kd*irradiance)*std::max(0.0f, l*normal);
	RGBColor ks = object.ks;
	//�߹�ָ��
	float p = 2.0;
	RGBColor specular = (ks*irradiance)*powf(normal*half, p);
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