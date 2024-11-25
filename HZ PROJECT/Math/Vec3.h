#pragma once
#include "Vec2.h"
class Vec3Dir;

class Vec3 :  public Vec2
{
public:
	Vec3() = default;
	Vec3(float x, float y, float z);

	Vec3 operator+(Vec3 rhs);
	Vec3 operator+(Vec3 rhs) const;
	Vec3 operator+=(Vec3 rhs);
	Vec3 operator+(Vec3Dir rhs);
	Vec3 operator+=(Vec3Dir rhs);
	Vec3 operator-(Vec3 rhs);
	Vec3 operator-(Vec3 rhs) const;
	Vec3 operator-=(Vec3 rhs);
	Vec3 operator*(float scl);
	Vec3 operator*(float scl) const;
	Vec3 operator*=(float scl);
	float operator* (Vec3 rhs); // dot product
	Vec3 operator/(float scl);
	Vec3 operator/(float scl) const;
	Vec3 operator/=(float scl);
	float GetLenghtSqr() const;
	float GetLenght() const;
	Vec3 Normalize();
	Vec3 Normalize() const;
	Vec3 CrossProduct(Vec3 lhs, Vec3 rhs);

public:
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float w = 1.0f;
};


class Vec3Dir : public Vec2Dir
{
public:
	Vec3Dir() = default;
	Vec3Dir(Vec3 endPoint, Vec3 startPoint);
	Vec3Dir operator*(float scl);
	Vec3Dir operator*(float scl) const;
	Vec3Dir operator*=(float scl);
	Vec3Dir operator/(float scl);
	Vec3Dir operator/(float scl) const;
	Vec3Dir operator/=(float scl);
	float GetLenghtSqr() const;
	float GetLenght() const;
	Vec3Dir Normalize();
	Vec3Dir Normalize() const;
	Vec3Dir CrossProduct(Vec3Dir lhs, Vec3Dir rhs);
	float DotProduct(Vec3Dir rhs);

public:
	Vec3 endPoint = Vec3(0.f, 0.f, 0.f);
	Vec3 startPoint = Vec3(0.f, 0.f, 0.f);
	float xLen = 0.f;
	float yLen = 0.f;
	float zLen = 0.f;
	float w = 1.0f;
};
