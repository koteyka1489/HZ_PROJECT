#include "Vec3.h"

Vec3::Vec3(float x, float y, float z)
	:
	x(x),
	y(y),
	z(z)
{}


Vec3 Vec3::operator+(Vec3 rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vec3 Vec3::operator+(Vec3 rhs) const
{
	Vec3 nVec{ this->x + rhs.x, this->y + rhs.y, this->z + rhs.z };
	return nVec;
}

Vec3 Vec3::operator+=(Vec3 rhs)
{
	return (*this) + rhs;
}

Vec3 Vec3::operator+(Vec3Dir rhs)
{
	this->x += rhs.xLen;
	this->y += rhs.yLen;
	this->z += rhs.zLen;
	return *this;
}

Vec3 Vec3::operator+=(Vec3Dir rhs)
{
	return (*this) + rhs;
}

Vec3 Vec3::operator-(Vec3 rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vec3 Vec3::operator-(Vec3 rhs) const
{
	Vec3 nVec{ this->x - rhs.x, this->y - rhs.y, this->z - rhs.z };
	return nVec;
}

Vec3 Vec3::operator-=(Vec3 rhs)
{
	return (*this) - rhs;
}

Vec3 Vec3::operator*(float scl)
{
	x *= scl;
	y *= scl;
	z *= scl;
	return *this;
}

Vec3 Vec3::operator*(float scl) const
{
	Vec3 nVec{ this->x * scl, this->y * scl, this->z * scl };
	return nVec;
}

Vec3 Vec3::operator*=(float scl)
{
	return (*this) * scl;
}

// dot product
float Vec3::operator*(Vec3 rhs)
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vec3 Vec3::operator/(float scl)
{
	x /= scl;
	y /= scl;
	z /= scl;
	return *this;
}



Vec3 Vec3::operator/(float scl) const
{
	Vec3 nVec{ this->x / scl, this->y / scl, this->z / scl };
	return nVec;
}

Vec3 Vec3::operator/=(float scl)
{
	return (*this) / scl;
}

float Vec3::GetLenghtSqr() const
{
	return x * x + y * y + z * z;
}

float Vec3::GetLenght() const
{
	return sqrt(this->GetLenghtSqr());
}

Vec3 Vec3::Normalize()
{

	if (this->GetLenght() != 0.f)
	{
		*this = (*this) / this->GetLenght();
	}
	return *this;
}

Vec3 Vec3::Normalize() const
{
	Vec3 normalize;
	if (this->GetLenght() != 0.f)
	{
		normalize = (*this) / this->GetLenght();
	}
	return normalize;
}

Vec3 Vec3::CrossProduct(Vec3 lhs, Vec3 rhs)
{
	return Vec3(
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x
	);
}






// Вектор направления
Vec3Dir::Vec3Dir(Vec3 endPoint, Vec3 startPoint)
	:
	endPoint(endPoint),
	startPoint(startPoint)
{
	xLen = endPoint.x - startPoint.x;
	yLen = endPoint.y - startPoint.y;
	zLen = endPoint.z - startPoint.z;
}

Vec3Dir Vec3Dir::operator*(float scl)
{
	endPoint.x *= scl;
	endPoint.y *= scl;
	endPoint.z *= scl;
	startPoint.x *= scl;
	startPoint.y *= scl;
	startPoint.z *= scl;
	xLen = endPoint.x - startPoint.x;
	yLen = endPoint.y - startPoint.y;
	zLen = endPoint.z - startPoint.z;
	return *this;
}

Vec3Dir Vec3Dir::operator*(float scl) const
{
	Vec3Dir nVecDir = *this;
	nVecDir.endPoint.x *= scl;
	nVecDir.endPoint.y *= scl;
	nVecDir.endPoint.z *= scl;
	nVecDir.startPoint.x *= scl;
	nVecDir.startPoint.y *= scl;
	nVecDir.startPoint.z *= scl;
	nVecDir.xLen = nVecDir.endPoint.x - nVecDir.startPoint.x;
	nVecDir.yLen = nVecDir.endPoint.y - nVecDir.startPoint.y;
	nVecDir.zLen = nVecDir.endPoint.z - nVecDir.startPoint.z;
	return nVecDir;
}

Vec3Dir Vec3Dir::operator*=(float scl)
{
	return (*this) * scl;
}

Vec3Dir Vec3Dir::operator/(float scl)
{
	endPoint.x /= scl;
	endPoint.y /= scl;
	endPoint.z /= scl;
	startPoint.x /= scl;
	startPoint.y /= scl;
	startPoint.z /= scl;
	xLen = endPoint.x - startPoint.x;
	yLen = endPoint.y - startPoint.y;
	zLen = endPoint.z - startPoint.z;
	return *this;
}

Vec3Dir Vec3Dir::operator/(float scl) const
{
	Vec3Dir nVecDir = (*this);
	nVecDir.endPoint.x /= scl;
	nVecDir.endPoint.y /= scl;
	nVecDir.endPoint.z /= scl;
	nVecDir.startPoint.x /= scl;
	nVecDir.startPoint.y /= scl;
	nVecDir.startPoint.z /= scl;
	nVecDir.xLen = nVecDir.endPoint.x - nVecDir.startPoint.x;
	nVecDir.yLen = nVecDir.endPoint.y - nVecDir.startPoint.y;
	nVecDir.zLen = nVecDir.endPoint.z - nVecDir.startPoint.z;
	return nVecDir;
}

Vec3Dir Vec3Dir::operator/=(float scl)
{
	return (*this) / scl;
}

float Vec3Dir::GetLenghtSqr() const
{
	return xLen * xLen + yLen * yLen + zLen * zLen;
}

float Vec3Dir::GetLenght() const
{
	return sqrt(this->GetLenghtSqr());
}

Vec3Dir Vec3Dir::Normalize()
{
	if (this->GetLenght() != 0.f)
	{
		*this = (*this) / this->GetLenght();
	}
	return *this;
}

Vec3Dir Vec3Dir::Normalize() const
{
	Vec3Dir nVecNormalize;

	if (this->GetLenght() != 0.f)
	{
		nVecNormalize = (*this) / this->GetLenght();
	}
	return nVecNormalize;
}

Vec3Dir Vec3Dir::CrossProduct(Vec3Dir lhs, Vec3Dir rhs)
{
	Vec3Dir vcp{ Vec3{0.f, 0.f, 0.f}, lhs.startPoint };
	vcp.xLen = lhs.yLen * rhs.zLen - lhs.zLen * rhs.yLen;
	vcp.yLen = lhs.zLen * rhs.xLen - lhs.xLen * rhs.zLen;
	vcp.zLen = lhs.xLen * rhs.yLen - lhs.yLen * rhs.xLen;
	vcp.endPoint.x = vcp.startPoint.x + vcp.xLen;
	vcp.endPoint.y = vcp.startPoint.y + vcp.yLen;
	vcp.endPoint.z = vcp.startPoint.z + vcp.zLen;
	return vcp;
}

float Vec3Dir::DotProduct(Vec3Dir rhs)
{
	return xLen * rhs.xLen + yLen * rhs.yLen + zLen * rhs.zLen;
}


