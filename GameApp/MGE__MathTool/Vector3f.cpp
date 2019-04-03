///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _MATHTOOL_EXPORT

#include "../MGE_Base/Type.h"
#include "MathTool.h"
#include "string.h"

Vector3f::Vector3f() {
	x = y = z = 0.0f;
}

Vector3f::Vector3f(float px, float py, float pz) {
	x = px;
	y = py;
	z = pz;
}

float Vector3f::Magnitude() {
	return sqrt( x * x + y * y + z * z );
}

Vector3f Vector3f::Normalized() {
	Vector3f desc;
	float m = Magnitude();
	desc.x = x / m;
	desc.y = y / m;
	desc.z = z / m;
	return desc;
}

Vector3f Vector3f::operator+(Vector3f src) {
	Vector3f desc;
	desc.x = x + src.x;
	desc.y = y + src.y;
	desc.z = z + src.z;
	return desc;
}

Vector3f &Vector3f::operator+=(Vector3f src) {
	(*this) = (*this) + src;
	return *this;
}

Vector3f Vector3f::operator-(Vector3f src) {
	Vector3f desc;
	desc.x = x - src.x;
	desc.y = y - src.y;
	desc.z = z - src.z;
	return desc;
}

Vector3f & Vector3f::operator-=(Vector3f src) {
	(*this) = (*this) - src;
	return *this;
}
	
Vector3f Vector3f::operator * (Matrix33f src) {
	Vector3f des;
	des.x = src.m[0][0] * x + src.m[1][0] * y + src.m[2][0] * z;
	des.y = src.m[0][1] * x + src.m[1][1] * y + src.m[2][1] * z;
	des.z = src.m[0][2] * x + src.m[1][2] * y + src.m[2][2] * z;
	return des;
}

Vector3f Vector3f::operator*(float scale) {
	Vector3f desc;
	desc.x = x * scale;
	desc.y = y * scale;
	desc.z = z * scale;
	return desc;
}

Vector3f & Vector3f::operator*=(float scale) {
	(*this) = (*this) * scale;
	return *this;
}

float Vector3f::operator*(Vector3f src) {
	return DotProduct(src);
}

Vector3f Vector3f::operator^(Vector3f src) {
	return CrossProduct(src);
}

Vector3f Vector3f::operator/(float scale) {
	Vector3f desc;
	desc.x = x / scale;
	desc.y = y / scale;
	desc.z = z / scale;
	return desc;
}

Vector3f &Vector3f::operator/=(float scale) {
	(*this) = (*this) / scale;
	return *this;
}

//Vector3f &Vector3f::operator=(Vector3f &src) {
//	x = src.x;
//	y = src.y;
//	z = src.z;
//	return *this;
//}

float &Vector3f::operator[]( unsigned int i ) {
	switch (i) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			return *(float*)NULL;
	}
}

float Vector3f::DotProduct(Vector3f src) {
	return x * src.x + y * src.y + z * src.z;
}

Vector3f Vector3f::CrossProduct(Vector3f src) {
	return Vector3f(
		y * src.z - z * src.y, //x
		z * src.x - x * src.z, //y
		x * src.y - y * src.x //z
	);
}

