#pragma once
#include <cmath>
class Vec2Dir;

class Vec2
{
public:
	Vec2() = default;
	Vec2(float x, float y);

	Vec2 operator+(Vec2 rhs);
	Vec2 operator+(Vec2 rhs) const;
	Vec2 operator+=(Vec2 rhs);
	Vec2 operator+(Vec2Dir rhs);
	Vec2 operator+=(Vec2Dir rhs);
	Vec2 operator-(Vec2 rhs);
	Vec2 operator-(Vec2 rhs) const;
	Vec2 operator-=(Vec2 rhs);
	Vec2 operator*(float scl);
	Vec2 operator*(float scl) const;
	Vec2 operator*=(float scl);
	float operator* (Vec2 rhs); // dot product
	Vec2 operator/(float scl);
	Vec2 operator/(float scl) const;
	Vec2 operator/=(float scl);
	float GetLenghtSqr() const;
	float GetLenght() const;
	Vec2 Normalize();
	Vec2 Normalize() const;

public:
	float x = 0.f;
	float y = 0.f;
	float w = 1.0f;
};


// Вектор направления
class Vec2Dir
{
public:
	Vec2Dir() = default;
	Vec2Dir(Vec2 endPoint, Vec2 startPoint);
	Vec2Dir operator*(float scl);
	Vec2Dir operator*(float scl) const;
	Vec2Dir operator*=(float scl);
	Vec2Dir operator/(float scl);
	Vec2Dir operator/(float scl) const;
	Vec2Dir operator/=(float scl);
	float GetLenghtSqr() const;
	float GetLenght() const;
	Vec2Dir Normalize();
	Vec2Dir Normalize() const;

public:
	Vec2 endPoint = Vec2(0.f, 0.f);
	Vec2 startPoint = Vec2(0.f, 0.f);
	float xLen = 0.f;
	float yLen = 0.f;
};

