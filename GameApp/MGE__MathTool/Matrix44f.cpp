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


Matrix44f::Matrix44f( const Vector3f &translation, const Matrix33f &rotation ) {
	m[0][0] = rotation.m[0][0]; m[0][1] = rotation.m[0][1]; m[0][2] = rotation.m[0][2]; m[0][3] = translation.x; 
	m[1][0] = rotation.m[1][0]; m[1][1] = rotation.m[1][1]; m[1][2] = rotation.m[1][2]; m[1][3] = translation.y; 
	m[2][0] = rotation.m[2][0]; m[2][1] = rotation.m[2][1]; m[2][2] = rotation.m[2][2]; m[2][3] = translation.z; 
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f; 
}



Matrix44f Matrix44f::operator + (Matrix44f src) {
	Matrix44f desc;
	desc.m[0][0] = m[0][0] + src.m[0][0];
	desc.m[1][0] = m[1][0] + src.m[1][0];
	desc.m[2][0] = m[2][0] + src.m[2][0];
	desc.m[3][0] = m[3][0] + src.m[3][0];
	desc.m[0][1] = m[0][1] + src.m[0][1];
	desc.m[1][1] = m[1][1] + src.m[1][1];
	desc.m[2][1] = m[2][1] + src.m[2][1];
	desc.m[3][1] = m[3][1] + src.m[3][1];
	desc.m[0][2] = m[0][2] + src.m[0][2];
	desc.m[1][2] = m[1][2] + src.m[1][2];
	desc.m[2][2] = m[2][2] + src.m[2][2];
	desc.m[3][2] = m[3][2] + src.m[3][2];
	desc.m[0][3] = m[0][3] + src.m[0][3];
	desc.m[1][3] = m[1][3] + src.m[1][3];
	desc.m[2][3] = m[2][3] + src.m[2][3];
	desc.m[3][3] = m[3][3] + src.m[3][3];
	return desc;
}

Matrix44f Matrix44f::operator - (Matrix44f src) {
	Matrix44f desc;
	desc.m[0][0] = m[0][0] - src.m[0][0];
	desc.m[1][0] = m[1][0] - src.m[1][0];
	desc.m[2][0] = m[2][0] - src.m[2][0];
	desc.m[3][0] = m[3][0] - src.m[3][0];
	desc.m[0][1] = m[0][1] - src.m[0][1];
	desc.m[1][1] = m[1][1] - src.m[1][1];
	desc.m[2][1] = m[2][1] - src.m[2][1];
	desc.m[3][1] = m[3][1] - src.m[3][1];
	desc.m[0][2] = m[0][2] - src.m[0][2];
	desc.m[1][2] = m[1][2] - src.m[1][2];
	desc.m[2][2] = m[2][2] - src.m[2][2];
	desc.m[3][2] = m[3][2] - src.m[3][2];
	desc.m[0][3] = m[0][3] - src.m[0][3];
	desc.m[1][3] = m[1][3] - src.m[1][3];
	desc.m[2][3] = m[2][3] - src.m[2][3];
	desc.m[3][3] = m[3][3] - src.m[3][3];
	return desc;
}

Matrix44f Matrix44f::operator * (Matrix44f src) {
	Matrix44f desc;
	desc.m[0][0] = m[0][0] * src.m[0][0] + m[0][1] * src.m[1][0] + m[0][2] * src.m[2][0] + m[0][3] * src.m[3][0] ;
	desc.m[1][0] = m[1][0] * src.m[0][0] + m[1][1] * src.m[1][0] + m[1][2] * src.m[2][0] + m[1][3] * src.m[3][0] ;
	desc.m[2][0] = m[2][0] * src.m[0][0] + m[2][1] * src.m[1][0] + m[2][2] * src.m[2][0] + m[2][3] * src.m[3][0] ;
	desc.m[3][0] = m[3][0] * src.m[0][0] + m[3][1] * src.m[1][0] + m[3][2] * src.m[2][0] + m[3][3] * src.m[3][0] ;
	desc.m[0][1] = m[0][0] * src.m[0][1] + m[0][1] * src.m[1][1] + m[0][2] * src.m[2][1] + m[0][3] * src.m[3][1] ;
	desc.m[1][1] = m[1][0] * src.m[0][1] + m[1][1] * src.m[1][1] + m[1][2] * src.m[2][1] + m[1][3] * src.m[3][1] ;
	desc.m[2][1] = m[2][0] * src.m[0][1] + m[2][1] * src.m[1][1] + m[2][2] * src.m[2][1] + m[2][3] * src.m[3][1] ;
	desc.m[3][1] = m[3][0] * src.m[0][1] + m[3][1] * src.m[1][1] + m[3][2] * src.m[2][1] + m[3][3] * src.m[3][1] ;
	desc.m[0][2] = m[0][0] * src.m[0][2] + m[0][1] * src.m[1][2] + m[0][2] * src.m[2][2] + m[0][3] * src.m[3][2] ;
	desc.m[1][2] = m[1][0] * src.m[0][2] + m[1][1] * src.m[1][2] + m[1][2] * src.m[2][2] + m[1][3] * src.m[3][2] ;
	desc.m[2][2] = m[2][0] * src.m[0][2] + m[2][1] * src.m[1][2] + m[2][2] * src.m[2][2] + m[2][3] * src.m[3][2] ;
	desc.m[3][2] = m[3][0] * src.m[0][2] + m[3][1] * src.m[1][2] + m[3][2] * src.m[2][2] + m[3][3] * src.m[3][2] ;
	desc.m[0][3] = m[0][0] * src.m[0][3] + m[0][1] * src.m[1][3] + m[0][2] * src.m[2][3] + m[0][3] * src.m[3][3] ;
	desc.m[1][3] = m[1][0] * src.m[0][3] + m[1][1] * src.m[1][3] + m[1][2] * src.m[2][3] + m[1][3] * src.m[3][3] ;
	desc.m[2][3] = m[2][0] * src.m[0][3] + m[2][1] * src.m[1][3] + m[2][2] * src.m[2][3] + m[2][3] * src.m[3][3] ;
	desc.m[3][3] = m[3][0] * src.m[0][3] + m[3][1] * src.m[1][3] + m[3][2] * src.m[2][3] + m[3][3] * src.m[3][3] ;
	return desc;
}

Matrix44f Matrix44f::operator * (float scale) {
	Matrix44f desc;
	desc.m[0][0] = m[0][0] * scale;
	desc.m[0][1] = m[0][1] * scale;
	desc.m[0][2] = m[0][2] * scale;
	desc.m[0][3] = m[0][3] * scale;
	desc.m[1][0] = m[1][0] * scale;
	desc.m[1][1] = m[1][1] * scale;
	desc.m[1][2] = m[1][2] * scale;
	desc.m[1][3] = m[1][3] * scale;
	desc.m[2][0] = m[2][0] * scale;
	desc.m[2][1] = m[2][1] * scale;
	desc.m[2][2] = m[2][2] * scale;
	desc.m[2][3] = m[2][3] * scale;
	desc.m[3][0] = m[3][0] * scale;
	desc.m[3][1] = m[3][1] * scale;
	desc.m[3][2] = m[3][2] * scale;
	desc.m[3][3] = m[3][3] * scale;
	return desc;
}

//Matrix44f& Matrix44f::operator = (Matrix44f &src) {
//	memcpy(&m , &src.m, sizeof(float) * 16);
//	return *this;
//}

Matrix44f& Matrix44f::operator *= (Matrix44f src) {
	(*this) = (*this) * src;
	return *this;
}

Matrix44f& Matrix44f::operator *= (float scale) {
	(*this) = (*this) * scale;
	return *this;
}

Matrix44f& Matrix44f::operator += (Matrix44f src) {
	(*this) = (*this) + src;
	return *this;
}

Matrix44f& Matrix44f::operator -= (Matrix44f src) {
	(*this) = (*this) - src;
	return *this;
}
	
Matrix33f Matrix44f::GetRotation() {
	Matrix33f m33( m[0][0], m[0][1], m[0][2],
	            m[1][0], m[1][1], m[1][2],
				m[2][0], m[2][1], m[2][2]
			   );

   	//--Extract Scale from first 3 rows--//
	float scale[3];
	for (int r = 0; r < 3; ++r) {
		//Get scale for this row
		scale[r] = Vector3f( m33.m[r][0], m33.m[r][1], m33.m[r][2] ).Magnitude();

		//Normalize the row by dividing each factor by scale
		m33.m[r][0] /= scale[r];
		m33.m[r][1] /= scale[r];
		m33.m[r][2] /= scale[r];
	}

	//Return result
	return m33;
}

float Matrix44f::GetScale() {
	const Matrix44f & m44 = *this;
	float scale[3];
	for (int r = 0; r < 3; ++r) {
		//Get scale for this row
		scale[r] = Vector3f( m44.m[r][0], m44.m[r][1], m44.m[r][2] ).Magnitude();
	}
	 
	//averate the scale since NIF doesn't support discreet scaling
	return (scale[0] + scale[1] + scale[2]) / 3.0f;
}


Vector3f Matrix44f::GetTranslation() {
	return Vector3f( m[0][3], m[1][3], m[2][3] );
}


Matrix33f Matrix44f::Submatrix( int skip_r, int skip_c ) {
	Matrix33f sub;
	int i = 0, j = 0;
	for (int r = 0; r < 4; r++) {
		if (r == skip_r) {
			continue;}
		for (int c = 0; c < 4; c++) {
			if (c == skip_c) {
				continue;}
			sub.m[i][j] = m[r][c];
			j++;
		}
		i++;
		j = 0;
	}
	return sub;
}


float Matrix44f::Adjoint( int skip_r, int skip_c ) {
	Matrix33f sub = Submatrix( skip_r, skip_c );
	return pow(-1.0f, float(skip_r + skip_c)) * sub.Determinant();
}

Matrix44f Matrix44f::Inverse() {
	Matrix22f P(m[0][0], m[0][1], m[1][0], m[1][1]);
	Matrix22f Q(m[0][2], m[0][3], m[1][2], m[1][3]);
	Matrix22f R(m[2][0], m[2][1], m[3][0], m[3][1]);
	Matrix22f S(m[2][2], m[2][3], m[3][2], m[3][3]);
	Matrix22f IP = P.Inverse();
	Matrix22f IPQ = IP * Q;
	Matrix22f RIP = R * IP;
	Matrix22f BS = (S - RIP * Q).Inverse();
	Matrix22f BR = BS * RIP * (-1.0f);
	Matrix22f BQ = IPQ * BS * (-1.0f);
	Matrix22f BP = IP - IPQ * BR;
	Matrix44f des;
	des.m[0][0] = BP.m[0][0]; des.m[0][1] = BP.m[0][1]; des.m[0][2] = BQ.m[0][0]; des.m[0][3] = BQ.m[0][1]; 
	des.m[1][0] = BP.m[1][0]; des.m[1][1] = BP.m[1][1]; des.m[1][2] = BQ.m[1][0]; des.m[1][3] = BQ.m[1][1]; 
	des.m[2][0] = BR.m[0][0]; des.m[2][1] = BR.m[0][1]; des.m[2][2] = BS.m[0][0]; des.m[2][3] = BS.m[0][1]; 
	des.m[3][0] = BR.m[1][0]; des.m[3][1] = BR.m[1][1]; des.m[3][2] = BS.m[1][0]; des.m[3][3] = BS.m[1][1]; 
	return des;
}

float Matrix44f::Determinant() {
	const Matrix44f & t = *this;
	return  t.m[0][0] * Submatrix(0, 0).Determinant()
	      - t.m[0][1] * Submatrix(0, 1).Determinant()
	      + t.m[0][2] * Submatrix(0, 2).Determinant()
	      - t.m[0][3] * Submatrix(0, 3).Determinant();
}

void Matrix44f::Decompose( Vector3f &translate, Matrix33f &rotation, float &scale ) {
	translate = Vector3f( m[3][0], m[3][1], m[3][2] );
	Matrix33f rotT;
	for ( int i = 0; i < 3; i++ ){
		for ( int j = 0; j < 3; j++ ){
			rotation.m[i][j] = m[i][j];
			rotT.m[j][i] = m[i][j];
		}
	}
	Matrix33f mtx = rotation * rotT;
	float scale3[3];
	scale3[0] = sqrt(mtx.m[0][0]);
	scale3[1] = sqrt(mtx.m[1][1]);
	scale3[2] = sqrt(mtx.m[2][2]);
	for ( int i = 0; i < 3; i++ ){
		for ( int j = 0; j < 3; j++ ){
			rotation.m[i][j] /= scale3[i];
		}
	}
	scale = (scale3[0] + scale3[1] + scale3[2]) / 3.0f;
}

void Matrix44f::Decompose( Vector3f &trans, Matrix33f &rot, Vector3f &scale ) {
	trans = Vector3f( m[3][0], m[3][1], m[3][2] );
	
	Matrix33f rotT;
	
	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			rot.m[j][i] = m[i][j];
			rotT.m[i][j] = m[i][j];
		}
	}
	
	Matrix33f mtx = rot * rotT;
	
	scale = Vector3f( sqrt( mtx.m[0][0] ), sqrt( mtx.m[1][1] ), sqrt( mtx.m[2][2] ) );
	
	for ( int i = 0; i < 3; i++ ) {
		for ( int j = 0; j < 3; j++ ) {
			rot.m[i][j] /= ((float*)&scale)[i];
		}
	}
}

void Matrix44f::Compose( Vector3f &trans, Matrix33f &rot, Vector3f &scale ) {
	m[0][3] = 0.0;
	m[1][3] = 0.0;
	m[2][3] = 0.0;
	m[3][3] = 1.0;

	m[3][0] = trans.x;
	m[3][1] = trans.y;
	m[3][2] = trans.z;
	
	for ( int i = 0; i < 3; i++ ) {
		for ( int j = 0; j < 3; j++ ) {
			m[i][j] = rot.m[j][i] * ((float*)&scale)[j];
		}
	}
}

Matrix44f Matrix44f::Rotate(Vector3f normal, float angle) {
	Matrix44f desc;
	float mag, s, c;
	float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;
	float x = normal.x;
	float y = normal.y;
	float z = normal.z;

	s = sinf(angle);
	c = cosf(angle);

	mag = sqrtf( x * x + y * y + z * z );

	// Identity matrix
	if (mag == 0.0) {
		return desc;
	}

	// Rotation matrix is normalized
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
	desc.m[3][0] = 0.0;

	desc.m[0][1] = (one_c * xy) + zs;
	desc.m[1][1] = (one_c * yy) + c;
	desc.m[2][1] = (one_c * yz) - xs;
	desc.m[3][1] = 0.0;

	desc.m[0][2] = (one_c * zx) - ys;
	desc.m[1][2] = (one_c * yz) + xs;
	desc.m[2][2] = (one_c * zz) + c;
	desc.m[3][2] = 0.0;

	desc.m[0][3] = 0.0;
	desc.m[1][3] = 0.0;
	desc.m[2][3] = 0.0;
	desc.m[3][3] = 1.0;
	return desc;
}

Matrix44f Matrix44f::Transpose() {
	Matrix44f desc;
	desc.m[0][0] = m[0][0];
	desc.m[0][1] = m[1][0];
	desc.m[0][2] = m[2][0];
	desc.m[0][3] = m[3][0];
	desc.m[1][0] = m[0][1];
	desc.m[1][1] = m[1][1];
	desc.m[1][2] = m[2][1];
	desc.m[1][3] = m[3][1];
	desc.m[2][0] = m[0][2];
	desc.m[2][1] = m[1][2];
	desc.m[2][2] = m[2][2];
	desc.m[2][3] = m[3][2];
	desc.m[3][0] = m[0][3];
	desc.m[3][1] = m[1][3];
	desc.m[3][2] = m[2][3];
	desc.m[3][3] = m[3][3];
	return desc;
}


Vector4f Matrix44f::operator* (Vector4f& v) {
	Vector4f des;
    des.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;	 
    des.x = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;	 
    des.x = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;	 
    des.x = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;	 
	return des;
}

Vector3f Matrix44f::operator* (Vector3f& v) {
	Vector3f des;
	des.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] *  v.z + m[0][3]; 
	des.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] *  v.z + m[1][3]; 
	des.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] *  v.z + m[2][3]; 
	return des;
}

float Matrix44f::MultiZ(Vector4f& src) {
	Vector4f &mz = *(Vector4f*)&m[2][0];
	return mz * src;
}
float Matrix44f::MultiZ(Vector3f& src) {
	Vector3f &mz = *(Vector3f*)&m[2][0];
	return mz * src + m[2][3];
}

Matrix44f::Matrix44f(float m11, float m12, float m13, float m14,
					 float m21, float m22, float m23, float m24,
					 float m31, float m32, float m33, float m34,
					 float m41, float m42, float m43, float m44) {
	m[0][0] = m11; m[0][1] = m12; m[0][2] = m13; m[0][3] = m14;
	m[1][0] = m21; m[1][1] = m22; m[1][2] = m23; m[1][3] = m24;
	m[2][0] = m31; m[2][1] = m32; m[2][2] = m33; m[2][3] = m34;
	m[3][0] = m41; m[3][1] = m42; m[3][2] = m43; m[3][3] = m44;
}


Matrix44f::Matrix44f() {
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

