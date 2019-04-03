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


Vector4f::Vector4f() {
	x = y = z = w = 0.0f;
}

Vector4f::Vector4f(float px, float py, float pz, float pw) {
	x = px;
	y = py;
	z = pz;
	w = pw;
}

float Vector4f::Magnitude() {
	return sqrt( x * x + y * y + z * z + w * w );
}

Vector4f Vector4f::Normalized() {
	Vector4f desc;
	float m = Magnitude();
	desc.x = x / m;
	desc.y = y / m;
	desc.z = z / m;
	desc.w = w / m;
	return desc;
}

Vector4f Vector4f::operator+(Vector4f src) {
	Vector4f desc;
	desc.x = x + src.x;
	desc.y = y + src.y;
	desc.z = z + src.z;
	desc.w = w + src.w;
	return desc;
}

Vector4f &Vector4f::operator+=(Vector4f src) {
	(*this) = (*this) + src;
	return *this;
}

Vector4f Vector4f::operator-(Vector4f src) {
	Vector4f desc;
	desc.x = x - src.x;
	desc.y = y - src.y;
	desc.z = z - src.z;
	desc.w = w - src.w;
	return desc;
}

Vector4f & Vector4f::operator-=(Vector4f src) {
	(*this) = (*this) - src;
	return *this;
}

Vector4f Vector4f::operator*(float scale) {
	Vector4f desc;
	desc.x = x * scale;
	desc.y = y * scale;
	desc.z = z * scale;
	desc.w = w * scale;
	return desc;
}

Vector4f & Vector4f::operator*=(float scale) {
	(*this) = (*this) * scale;
	return *this;
}

float Vector4f::operator*(Vector4f src) {
	return x * src.x + y * src.y + z * src.z + w * src.w;
}

Vector4f Vector4f::operator/(float scale) {
	Vector4f desc;
	desc.x = x / scale;
	desc.y = y / scale;
	desc.z = z / scale;
	desc.w = w / scale;
	return desc;
}

Vector4f & Vector4f::operator/=(float scale) {
	(*this) = (*this) / scale;
	return *this;
}

//Vector4f & Vector4f::operator=(Vector4f &src) {
//	x = src.x;
//	y = src.y;
//	z = src.z;
//	w = src.w;
//	return *this;
//}

float &Vector4f::operator[]( unsigned int i ) {
	switch (i) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		default:
			return *(float*)NULL;
	}
}
