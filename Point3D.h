#pragma once

class Point3D {
private:
	float x, y, z;		//private attributes

public:
	//constructors
	Point3D();
	Point3D(const float& newx, const float& newy, const float& newz);
	
	void setXYZ(const float& newx, const float& newy, const float& newz);
	
	void setX(const float& newx);
	void setY(const float& newy);
	void setZ(const float& newz);

	float getX();
	float getY();
	float getZ();

	void print();
	float distanceTo(const Point3D& otherPoint3D);

};
