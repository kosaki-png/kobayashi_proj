#include "Vector3.h"
#include<cmath>


Vector3::Vector3()
	:Vector3(0,0,0)
{


}
Vector3::Vector3(float x, float y, float z)
	:XMFLOAT3{x,y,z}
{

}
float Vector3::length()const
{
	return std::sqrt(x*x + y * y + z * z);
}
float Vector3::lengthsq() const
{
	return (x*x+y*y+z*z);
}
Vector3& Vector3::normalize()
{
	float len = length();
	if (len != 0)
	{
		return *this /= len;
	}
	return *this;
}
float Vector3::dot(const Vector3& v)const
{
	return x * v.x + y * v.y; +z * v.z;
}
Vector3& Vector3::cross(const Vector3& v)const
{
	Vector3 a;
	a.x = y * v.z - z * v.y;
	a.y = z * v.x - x * v.z;
	a.z = x * v.y - y * v.x;
	return a;
}
Vector3 Vector3::operator+()const
{
	return  *this;
}
Vector3 Vector3::operator-()const
{
	return Vector3(-x, -y,-z);
}
Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
Vector3& Vector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}
Vector3& Vector3::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}
const Vector3 operator+(const Vector3 & v1, const Vector3 & v2)
{
	Vector3 temp(v1);
	return temp += v2;
}
const Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp -= v2;
}
const Vector3 operator*(const Vector3& v, float s)
{
	Vector3 temp(v);
	return  temp *= s;
}
const Vector3 operator*(float s, const Vector3& v)
{
	return v * s;
}
const Vector3 operator/(const Vector3& v, float s)
{
	Vector3 temp(v);
	return  temp /= s;
}
const Vector3 lerp(const Vector3& start, const Vector3& end, const float t)
{
	return start * (1.0f - t) + end * t;
}
const Vector3 easeIn(const Vector3& start, const Vector3& end, const float t)
{
	return start * (1.0f - t*t) + end * t*t;
}
const Vector3 easeOut(const Vector3& start, const Vector3& end, const float t)
{
	return start * (1.0f - t*(2-t))+end * t*(2-t);
}
const Vector3 easeInOut(const Vector3& start, const Vector3& end, const float t)
{
	return start * (1.0f - t*t * (3 - 2*t)) + end * t*t*(3 - 2*t);
}
