#pragma once

#include <itkMatrix.h>
#include <itkRGBPixel.h>
#include <itkImage.h>
typedef typename itk::Matrix<float, 4, 4> Matrix4;
typedef typename itk::Matrix<float, 3, 3> Matrix3;
typedef typename itk::Matrix<float, 2, 2> Matrix2;
typedef typename itk::Matrix<float, 2, 3> Matrix2x3;
typedef typename itk::Vector< float, 3 > Vector3;
typedef typename itk::Vector< float, 4 > Vector4;
typedef typename itk::Point<float, 4U> Point4;
typedef typename itk::Point<float, 3U> Point3;
typedef typename itk::Point<float, 2U> Point2;

typedef typename itk::RGBPixel< unsigned char > ImagePixelType;
typedef typename itk::Image< ImagePixelType, 2 > ImageType;