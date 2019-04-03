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


Matrix33f::Matrix33f(float m11, float m12, float m13,
					 float m21, float m22, float m23,
					 float m31, float m32, float m33) 
{
	m[0][0] = m11; m[0][1] = m12; m[0][2] = m13;
	m[1][0] = m21; m[1][1] = m22; m[1][2] = m23;
	m[2][0] = m31; m[2][1] = m32; m[2][2] = m33;
}

Matrix33f::Matrix33f(Vector3f v0, Vector3f v1, Vector3f v2) {
	m[0][0] = v0.x; m[0][1] = v0.y; m[0][2] = v0.z;
	m[1][0] = v1.x; m[1][1] = v1.y; m[1][2] = v1.z;
	m[2][0] = v2.x; m[2][1] = v2.y; m[2][2] = v2.z;
}

Matrix33f::Matrix33f() {
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
}

Matrix33f Matrix33f::operator + (Matrix33f src) {
	Matrix33f desc;
	desc.m[0][0] = m[0][0] + src.m[0][0];
	desc.m[1][0] = m[1][0] + src.m[1][0];
	desc.m[2][0] = m[2][0] + src.m[2][0];
	desc.m[0][1] = m[0][1] + src.m[0][1];
	desc.m[1][1] = m[1][1] + src.m[1][1];
	desc.m[2][1] = m[2][1] + src.m[2][1];
	desc.m[0][2] = m[0][2] + src.m[0][2];
	desc.m[1][2] = m[1][2] + src.m[1][2];
	desc.m[2][2] = m[2][2] + src.m[2][2];
	return desc;
}

Matrix33f Matrix33f::operator - (Matrix33f src) {
	Matrix33f desc;
	desc.m[0][0] = m[0][0] - src.m[0][0];
	desc.m[1][0] = m[1][0] - src.m[1][0];
	desc.m[2][0] = m[2][0] - src.m[2][0];
	desc.m[0][1] = m[0][1] - src.m[0][1];
	desc.m[1][1] = m[1][1] - src.m[1][1];
	desc.m[2][1] = m[2][1] - src.m[2][1];
	desc.m[0][2] = m[0][2] - src.m[0][2];
	desc.m[1][2] = m[1][2] - src.m[1][2];
	desc.m[2][2] = m[2][2] - src.m[2][2];
	return desc;
}

Matrix33f Matrix33f::operator * (float scale) {
	Matrix33f desc;
	desc.m[0][0] = m[0][0] * scale;
	desc.m[1][0] = m[1][0] * scale;
	desc.m[2][0] = m[2][0] * scale;
	desc.m[0][1] = m[0][1] * scale;
	desc.m[1][1] = m[1][1] * scale;
	desc.m[2][1] = m[2][1] * scale;
	desc.m[0][2] = m[0][2] * scale;
	desc.m[1][2] = m[1][2] * scale;
	desc.m[2][2] = m[2][2] * scale;
	return desc;
}

Matrix33f Matrix33f::operator * (Matrix33f src) {
	Matrix33f desc;
	desc.m[0][0] = m[0][0] * src.m[0][0] + m[0][1] * src.m[1][0] + m[0][2] * src.m[2][0] ;
	desc.m[1][0] = m[1][0] * src.m[0][0] + m[1][1] * src.m[1][0] + m[1][2] * src.m[2][0] ;
	desc.m[2][0] = m[2][0] * src.m[0][0] + m[2][1] * src.m[1][0] + m[2][2] * src.m[2][0] ;
	desc.m[0][1] = m[0][0] * src.m[0][1] + m[0][1] * src.m[1][1] + m[0][2] * src.m[2][1] ;
	desc.m[1][1] = m[1][0] * src.m[0][1] + m[1][1] * src.m[1][1] + m[1][2] * src.m[2][1] ;
	desc.m[2][1] = m[2][0] * src.m[0][1] + m[2][1] * src.m[1][1] + m[2][2] * src.m[2][1] ;
	desc.m[0][2] = m[0][0] * src.m[0][2] + m[0][1] * src.m[1][2] + m[0][2] * src.m[2][2] ;
	desc.m[1][2] = m[1][0] * src.m[0][2] + m[1][1] * src.m[1][2] + m[1][2] * src.m[2][2] ;
	desc.m[2][2] = m[2][0] * src.m[0][2] + m[2][1] * src.m[1][2] + m[2][2] * src.m[2][2] ;
	return desc;
}

Vector3f Matrix33f::operator* (Vector3f v) {
	Vector3f des;
	des.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] *  v.z; 
	des.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] *  v.z; 
	des.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] *  v.z; 
	return des;
}

Matrix33f Matrix33f::Rotate(Vector3f normal, float angle) {
	Matrix33f desc;
	float mag, s, c;
	float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;
	float x = normal.x;
	float y = normal.y;
	float z = normal.z;

	s = sinf(angle);
	c = cosf(angle);

	mag = sqrtf( x * x + y * y + z * z );
	if (mag == 0.0f) {
		Matrix33f desc;
		return desc;
	}

	x /= mag;
	y /= mag;
	z /= mag;

	xx = x * x;
	yy = y * y;
	zz = z * z;
	xy = x * y;
	yz = y * z;
	zx = z * x;
	xs = x * s;
	ys = y * s;
	zs = z * s;
	one_c = 1.0f - c;
	desc.m[0][0] = (one_c * xx) + c;
	desc.m[1][0] = (one_c * xy) - zs;
	desc.m[2][0] = (one_c * zx) + ys;

	desc.m[0][1] = (one_c * xy) + zs;
	desc.m[1][1] = (one_c * yy) + c;
	desc.m[2][1] = (one_c * yz) - xs;

	desc.m[0][2] = (one_c * zx) - ys;
	desc.m[1][2] = (one_c * yz) + xs;
	desc.m[2][2] = (one_c * zz) + c;
	return desc;
}

Matrix33f Matrix33f::Transpose() {
	Matrix33f desc;
	desc.m[0][0] = m[0][0];
	desc.m[0][1] = m[1][0];
	desc.m[0][2] = m[2][0];
	desc.m[1][0] = m[0][1];
	desc.m[1][1] = m[1][1];
	desc.m[1][2] = m[2][1];
	desc.m[2][0] = m[0][2];
	desc.m[2][1] = m[1][2];
	desc.m[2][2] = m[2][2];
	return desc;
}

//Matrix33f& Matrix33f::operator = (Matrix33f &src) {
//	memcpy(&m , &src.m, sizeof(float) * 9);
//	return *this;
//}


Quaternion Matrix33f::AsQuaternion() {
	Quaternion quat;
	float tr, s, q[4];
	int i, j, k;

	int nxt[3] = {1, 2, 0};

	tr = m[0][0] + m[1][1] + m[2][2];

	// check if the trace is positive or negative
	if (tr > 0.0) {
		s = sqrt (tr + 1.0f);
		quat.w = s / 2.0f;
		s = 0.5f / s;
		quat.x = (m[1][2] - m[2][1]) * s;
		quat.y = (m[2][0] - m[0][2]) * s;
		quat.z = (m[0][1] - m[1][0]) * s;
	}
	else {
		// trace is negative
		i = 0;
		if ( m[1][1] > m[0][0])
			i = 1;
		if ( m[2][2] > m[i][i] )
			i = 2;
		j = nxt[i];
		k = nxt[j];

		s = sqrt( ( m[i][i] - (m[j][j] + m[k][k]) ) + 1.0f );
		q[i] = s * 0.5f;
		if (s != 0.0f) s = 0.5f / s;
		q[3] = (m[j][k] - m[k][j]) * s;
		q[j] = (m[i][j] + m[j][i]) * s;
		q[k] = (m[i][k] + m[k][i]) * s;
		quat.x = q[0];
		quat.y= q[1];
		quat.z = q[2];
		quat.w = q[3];
	}

	return quat;
}

float Matrix33f::Determinant() {
	return  m[0][0] * ( m[1][1] * m[2][2] - m[1][2] * m[2][1] )
		  - m[0][1] * ( m[1][0] * m[2][2] - m[1][2] * m[2][0] )
		  + m[0][2] * ( m[1][0] * m[2][1] - m[1][1] * m[2][0] );
}


void Matrix33f::fromQuat( Quaternion &src)
{
	float fTx  = 2.0f * src.x;
	float fTy  = 2.0f * src.y;
	float fTz  = 2.0f * src.z;
	float fTwx = fTx*src.w;
	float fTwy = fTy*src.w;
	float fTwz = fTz*src.w;
	float fTxx = fTx*src.x;
	float fTxy = fTy*src.x;
	float fTxz = fTz*src.x;
	float fTyy = fTy*src.y;
	float fTyz = fTz*src.y;
	float fTzz = fTz*src.z;
	
	m[0][0] = 1.0f-(fTyy+fTzz);
	m[0][1] = fTxy-fTwz;
	m[0][2] = fTxz+fTwy;
	m[1][0] = fTxy+fTwz;
	m[1][1] = 1.0f-(fTxx+fTzz);
	m[1][2] = fTyz-fTwx;
	m[2][0] = fTxz-fTwy;
	m[2][1] = fTyz+fTwx;
	m[2][2] = 1.0f-(fTxx+fTyy);
}

Quaternion Matrix33f::toQuat() {
	Quaternion des;
	
	float trace = m[0][0] + m[1][1] + m[2][2];
	float root;
	
	if (trace > 0.0) {
		root = sqrt( trace + 1.0f );
		des.w = root / 2.0f;
		root = 0.5f / root;
		des.x = ( m[2][1] - m[1][2] ) * root;
		des.y = ( m[0][2] - m[2][0] ) * root;
		des.z = ( m[1][0] - m[0][1] ) * root;
	} else {
		int i = ( m[1][1] > m[0][0] ? 1 : 0 );
		if ( m[2][2] > m[i][i] )
			i = 2;
		const int next[3] = { 1, 2, 0 };
		int j = next[i];
		int k = next[j];

		root = sqrt( m[i][i] - m[j][j] - m[k][k] + 1.0f );
		((float*)&des)[i+1] = root / 2;
		root = 0.5f / root;
		((float*)&des)[0]   = ( m[k][j] - m[j][k] ) * root;
		((float*)&des)[j+1] = ( m[j][i] + m[i][j] ) * root;
		((float*)&des)[k+1] = ( m[k][i] + m[i][k] ) * root;
	}
	return des;
}

void Matrix33f::fromEuler( float x, float y, float z )
{
	float sinX = sin( x );
	float cosX = cos( x );
	float sinY = sin( y );
	float cosY = cos( y );
	float sinZ = sin( z );
	float cosZ = cos( z );
	
	m[0][0] = cosY * cosZ;
	m[0][1] = - cosY * sinZ;
	m[0][2] = sinY;
	m[1][0] = sinX * sinY * cosZ + sinZ * cosX;
	m[1][1] = cosX * cosZ - sinX * sinY * sinZ;
	m[1][2] = - sinX * cosY;
	m[2][0] = sinX * sinZ - cosX * sinY * cosZ;
	m[2][1] = cosX * sinY * sinZ + sinX * cosZ;
	m[2][2] = cosX * cosY;
}

BOOL8 Matrix33f::toEuler( float &x, float &y, float &z ) {
	if ( m[0][2] < 1.0 ) {
		if ( m[0][2] > - 1.0 ) {
			x = atan2( - m[1][2], m[2][2] );
			y = asin( m[0][2] );
			z = atan2( - m[0][1], m[0][0] );
			return TRUE;
		} else {
			x = - atan2( - m[1][0], m[1][1] );
			y = - PI / 2;
			z = 0.0;
			return FALSE;
		}
	} else {
		x = atan2( m[1][0], m[1][1] );
		y = PI / 2;
		z = 0.0;
		return FALSE;
	}
}
