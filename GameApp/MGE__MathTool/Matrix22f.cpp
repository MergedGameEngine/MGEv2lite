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

Matrix22f::Matrix22f() {
	m[0][0] = 1.0f; m[0][1] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f;
}

Matrix22f::Matrix22f(float m11, float m12,
					 float m21, float m22) {
	m[0][0] = m11; m[0][1] = m12;
	m[1][0] = m21; m[1][1] = m22;
}

Matrix22f Matrix22f::Inverse() {
	float idet22 = m[0][0] * m[1][1] - m[0][1] * m[1][0];
	if (idet22 == 0.0f) {
		return Matrix22f(0.0f, 0.0f, 0.0f, 0.0f);
	}
	Matrix22f des;
	des.m[0][0] = m[1][1] / idet22;
	des.m[0][1] = m[0][1] / idet22 / -1.0f;
	des.m[1][0] = m[1][0] / idet22 / -1.0f;
	des.m[1][1] = m[0][0] / idet22;
	return des;
}

Matrix22f Matrix22f::operator + (Matrix22f src) {
	Matrix22f desc;
	desc.m[0][0] = m[0][0] + src.m[0][0];
	desc.m[1][0] = m[1][0] + src.m[1][0];
	desc.m[0][1] = m[0][1] + src.m[0][1];
	desc.m[1][1] = m[1][1] + src.m[1][1];
	return desc;
}
Matrix22f Matrix22f::operator - (Matrix22f src) {
	Matrix22f desc;
	desc.m[0][0] = m[0][0] - src.m[0][0];
	desc.m[1][0] = m[1][0] - src.m[1][0];
	desc.m[0][1] = m[0][1] - src.m[0][1];
	desc.m[1][1] = m[1][1] - src.m[1][1];
	return desc;
}
Matrix22f Matrix22f::operator * (float src) {
	Matrix22f desc;
	desc.m[0][0] = m[0][0] * src;
	desc.m[1][0] = m[1][0] * src;
	desc.m[0][1] = m[0][1] * src;
	desc.m[1][1] = m[1][1] * src;
	return desc;
}

Matrix22f Matrix22f::operator * (Matrix22f src) {
	Matrix22f desc;
	desc.m[0][0] = m[0][0] * src.m[0][0] + m[0][1] * src.m[1][0] ;
	desc.m[1][0] = m[1][0] * src.m[0][0] + m[1][1] * src.m[1][0] ;
	desc.m[0][1] = m[0][0] * src.m[0][1] + m[0][1] * src.m[1][1] ;
	desc.m[1][1] = m[1][0] * src.m[0][1] + m[1][1] * src.m[1][1] ;
	return desc;
}
//Matrix22f& Matrix22f::operator = (Matrix22f& src) {
//	memcpy(&m , &src.m, sizeof(float) * 4);
//	return *this;
//}
