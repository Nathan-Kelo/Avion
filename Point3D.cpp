#include "Point3D.h"

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>



Point3D::Point3D()
{
	x = (float)(std::rand() % 100);
	y = (float)(std::rand() % 100);
	z = (float)(std::rand() % 100);
}

Point3D::Point3D(const float& newx, const float& newy, const float& newz):x(newx),y(newy),z(newz){}

void Point3D::setXYZ(const float& newx, const float& newy, const float& newz)
{
	x = newx;
	y = newy;
	z = newz;
}

void Point3D::setX(const float& newx)
{
	x = newx;
}

void Point3D::setY(const float& newy)
{
	y = newy;
}

void Point3D::setZ(const float& newz)
{
	z = newz;
}

float Point3D::getX()
{
	return x;
}

float Point3D::getY()
{
	return y;
}

float Point3D::getZ()
{
	return z;
}

void Point3D::print()
{
	std::cout << "\nX : " << x << "\nY : " << y << "\nZ : " << z << std::endl;
}

float Point3D::distanceTo(const Point3D &otherPoint3D)
{
	return sqrt((x-otherPoint3D.x)* (x - otherPoint3D.x) +(y- otherPoint3D.y)* (y - otherPoint3D.y) +(z- otherPoint3D.z)* (z - otherPoint3D.z));
}

