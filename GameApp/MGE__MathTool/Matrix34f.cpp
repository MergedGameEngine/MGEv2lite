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


Matrix34f::Matrix34f() {
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
}

Matrix34f::Matrix34f(Matrix33f r ) {
	//Set this matrix with rotate and translate information
	Matrix34f &m34 = *this;
	m34.m[0][0] = r.m[0][0];  m34.m[0][1] = r.m[0][1];  m34.m[0][2] = r.m[0][2];  m34.m[0][3] = 0.0f;
	m34.m[1][0] = r.m[1][0];  m34.m[1][1] = r.m[1][1];  m34.m[1][2] = r.m[1][2];  m34.m[1][3] = 0.0f;
	m34.m[2][0] = r.m[2][0];  m34.m[2][1] = r.m[2][1];  m34.m[2][2] = r.m[2][2];  m34.m[2][3] = 0.0f;
}

Matrix34f::Matrix34f(float m11, float m12, float m13, float m14,
					 float m21, float m22, float m23, float m24,
					 float m31, float m32, float m33, float m34) {
	m[0][0] = m11; m[0][1] = m12; m[0][2] = m13; m[0][3] = m14;
	m[1][0] = m21; m[1][1] = m22; m[1][2] = m23; m[1][3] = m24;
	m[2][0] = m31; m[2][1] = m32; m[2][2] = m33; m[2][3] = m34;
}

Matrix34f Matrix34f::operator*(Matrix34f src) {
	Matrix34f desc;
	float t;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			t = 0.0f;
			for (int k = 0; k < 3; k++) {
				t += m[i][k] * src.m[k][j];
			}
			desc.m[i][j] = t;
		}
	}

	return desc;
}

Matrix34f &Matrix34f::operator*=(Matrix34f src) {
	(*this) = (*this) * src;
	return *this;
}

Matrix34f Matrix34f::operator*( float scale) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] *= scale;
		}
	}
	return *this;
}

Matrix34f &Matrix34f::operator*=( float scale) {
	(*this) = (*this) * scale;
	return *this;
}

Vector3f Matrix34f::operator*(Vector3f src) {
	Vector3f desc;
	//Multiply, ignoring w
	desc.x = src.x * m[0][0] + src.y * m[1][0] + src.z * m[2][0];
	desc.y = src.x * m[0][1] + src.y * m[1][1] + src.z * m[2][1];
	desc.z = src.x * m[0][2] + src.y * m[1][2] + src.z * m[2][2];
	return desc;
}

Matrix34f Matrix34f::operator+(Matrix34f src) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] += src.m[i][j];
		}
	}
	return *this;
} 

Matrix34f &Matrix34f::operator+=(Matrix34f src) {
	(*this) = (*this) + src;
	return *this;
}

//Matrix34f &Matrix34f::operator=(Matrix34f &src) {
//	memcpy(m, src.m, sizeof(float) * 12);
//	return *this;
//}

Matrix34f Matrix34f::Transpose() {
	return Matrix34f(
		m[0][0], m[1][0], m[2][0], m[3][0],
		m[0][1], m[1][1], m[2][1], m[3][1],
		m[0][2], m[1][2], m[2][2], m[3][2]);
}

Matrix33f Matrix34f::Submatrix( int skip_r, int skip_c ) {
	Matrix33f sub;
	int i = 0, j = 0;
	for (int r = 0; r < 3; r++) {
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

float Matrix34f::Adjoint( int skip_r, int skip_c ) {
	Matrix33f sub = Submatrix( skip_r, skip_c );
	return pow(-1.0f, float(skip_r + skip_c)) * sub.Determinant();
}

Matrix34f Matrix34f::Inverse() {
	Matrix34f result;

	float det = Determinant();
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 4; c++) {
			result.m[c][r] = Adjoint(r, c) / det;
		}
	}

	return result;
}

float Matrix34f::Determinant() {
	return  m[0][0] * Submatrix(0, 0).Determinant()
		- m[0][1] * Submatrix(0, 1).Determinant()
		+ m[0][2] * Submatrix(0, 2).Determinant()
		- m[0][3] * Submatrix(0, 3).Determinant();
}

