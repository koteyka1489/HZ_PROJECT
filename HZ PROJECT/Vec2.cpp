#include "Vec2.h"




Vec2::Vec2(float x, float y)
	:
	x(x),
	y(y)
{}

Vec2 Vec2::operator+(Vec2 rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vec2 Vec2::operator+(Vec2 rhs) const
{
	Vec2 nVec{ this->x + rhs.x, this->y +  rhs.y };
	return nVec;
}

Vec2 Vec2::operator+=(Vec2 rhs)
{
	return (*this) + rhs;
}

Vec2 Vec2::operator+(Vec2Dir rhs)
{
	x += rhs.xLen;
	y += rhs.yLen;
	return *this;
}

Vec2 Vec2::operator+=(Vec2Dir rhs)
{

	return (*this) + rhs;
}

Vec2 Vec2::operator-(Vec2 rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vec2 Vec2::operator-(Vec2 rhs) const
{

	Vec2 nVec{ this->x - rhs.x, this->y - rhs.y };
	return nVec;
}

Vec2 Vec2::operator-=(Vec2 rhs)
{
	return (*this) - rhs;
}

Vec2 Vec2::operator*(float scl)
{
	x *= scl;
	y *= scl;
	return *this;
}

Vec2 Vec2::operator*(float scl) const
{
	Vec2 nVec{ this->x * scl, this->y * scl };
	return nVec;
}

Vec2 Vec2::operator*=(float scl)
{
	return (*this) * scl;
}

// dot product
float Vec2::operator*(Vec2 rhs)
{
	return x * rhs.x + y * rhs.y;
}

Vec2 Vec2::operator/(float scl)
{
	x /= scl;
	y /= scl;
	return *this;
}



Vec2 Vec2::operator/(float scl) const
{
	Vec2 nVec{ this->x / scl, this->y / scl };
	return nVec;
}

Vec2 Vec2::operator/=(float scl)
{
	return (*this) / scl;
}

float Vec2::GetLenghtSqr() const
{
	return x * x + y * y;
}

float Vec2::GetLenght() const
{
	return sqrt(this->GetLenghtSqr());
}

Vec2 Vec2::Normalize()
{
	
	if (this->GetLenght() != 0.f)
	{
		*this = (*this) / this->GetLenght();
	}
	return *this;
}

Vec2 Vec2::Normalize() const
{
	Vec2 normalize;
	if (this->GetLenght() != 0.f)
	{
		normalize = (*this) / this->GetLenght();
	}
	return normalize;
}






// Вектор направления
Vec2Dir::Vec2Dir(Vec2 endPoint, Vec2 startPoint)
	:
	endPoint(endPoint),
	startPoint(startPoint)
{
	xLen = endPoint.x - startPoint.x;
	yLen = endPoint.y - startPoint.y;
}

Vec2Dir Vec2Dir::operator*(float scl)
{
	endPoint.x *= scl;
	endPoint.y *= scl;
	startPoint.x *= scl;
	startPoint.y *= scl;
	xLen = endPoint.x - startPoint.x;
	yLen = endPoint.y - startPoint.y;
	return *this;
}

Vec2Dir Vec2Dir::operator*(float scl) const
{
	Vec2Dir nVecDir = *this;
	nVecDir.endPoint.x *= scl;
	nVecDir.endPoint.y *= scl;
	nVecDir.startPoint.x *= scl;
	nVecDir.startPoint.y *= scl;
	nVecDir.xLen = nVecDir.endPoint.x - nVecDir.startPoint.x;
	nVecDir.yLen = nVecDir.endPoint.y - nVecDir.startPoint.y;
	return nVecDir;
}

Vec2Dir Vec2Dir::operator*=(float scl)
{
	return (*this) * scl;
}

Vec2Dir Vec2Dir::operator/(float scl)
{
	endPoint.x /= scl;
	endPoint.y /= scl;
	startPoint.x /= scl;
	startPoint.y /= scl;
	xLen = endPoint.x - startPoint.x;
	yLen = endPoint.y - startPoint.y;
	return *this;
}

Vec2Dir Vec2Dir::operator/(float scl) const
{
	Vec2Dir nVecDir = *this;
	nVecDir.endPoint.x /= scl;
	nVecDir.endPoint.y /= scl;
	nVecDir.startPoint.x /= scl;
	nVecDir.startPoint.y /= scl;
	nVecDir.xLen = nVecDir.endPoint.x - nVecDir.startPoint.x;
	nVecDir.yLen = nVecDir.endPoint.y - nVecDir.startPoint.y;
	return nVecDir;
}

Vec2Dir Vec2Dir::operator/=(float scl)
{
	return (*this) / scl;
}

float Vec2Dir::GetLenghtSqr() const
{
	return xLen * xLen + yLen * yLen;
}

float Vec2Dir::GetLenght() const
{
	return sqrt(this->GetLenghtSqr());
}

Vec2Dir Vec2Dir::Normalize()
{
	if (this->GetLenght() != 0.f)
	{
		*this = (*this) / this->GetLenght();
	}
	return *this;
}

Vec2Dir Vec2Dir::Normalize() const
{
	Vec2Dir nVecNormalize;

	if (this->GetLenght() != 0.f)
	{
		nVecNormalize = (*this) / this->GetLenght();
	}
	return nVecNormalize;
}
