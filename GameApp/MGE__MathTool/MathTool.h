///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#ifndef _MATHTOOL_H_
#define _MATHTOOL_H_

#include "math.h"
#include "../MGE_Base/Type.h"

#ifndef PI
#define PI 3.14159265358979323846f  //Probably more accurate than a float can be, but it will just be rounded off anyway
#endif

struct Triangle;
struct TexCoord2f;
struct TexCoord3f;
struct Vector3f;
struct Vector4f;
struct Matrix22f;
struct Matrix33f;
struct Matrix44f;
struct Matrix34f;
struct Quaternion;

extern "C" struct Triangle {
	unsigned short a;
	unsigned short b;
	unsigned short c;
	Triangle();
	Triangle(unsigned short pa, unsigned short pb, unsigned short pc);
};

extern "C" struct Vector3f {
	float x;
	float y;
	float z;
	Vector3f();
	Vector3f(float x, float y, float z);
	float Magnitude();
	Vector3f Normalized();
	Vector3f operator + (Vector3f src);
	Vector3f operator - (Vector3f src);
	Vector3f operator * (float scale);
	Vector3f operator * (Matrix33f src);
	Vector3f operator / (float scale);
	float operator * (Vector3f src);
	Vector3f operator ^ (Vector3f src);
//	Vector3f& operator = (Vector3f &src);
	Vector3f& operator += (Vector3f src);
	Vector3f& operator -= (Vector3f src);
	Vector3f& operator *= (float scale);
	Vector3f& operator /= (float scale);
	float& operator[]( unsigned int i );
	float DotProduct( Vector3f src );
	Vector3f CrossProduct( Vector3f src); //Cross Product

};

extern "C" struct Vector4f {
	float x;
	float y;
	float z;
	float w;
	Vector4f();
	Vector4f(float x, float y, float z, float w);
	float Magnitude();
	Vector4f Normalized();
	Vector4f operator + (Vector4f src);
	Vector4f operator - (Vector4f src);
	Vector4f operator * (float scale);
	Vector4f operator / (float scale);
	float operator * (Vector4f src);
	//Vector4f operator ^ (Vector4f &src);
//	Vector4f& operator = (Vector4f &src);
	Vector4f& operator += (Vector4f src);
	Vector4f& operator -= (Vector4f src);
	Vector4f& operator *= (float scale);
	Vector4f& operator /= (float scale);
	float& operator[]( unsigned int i );
	//float DotProduct( Vector4f &src );
	//Vector4f CrossProduct( Vector4f &src); //Cross Product
};

extern "C" struct Quaternion {
	float w; //!< The W scalar component of this Quaternion.
	float x; //!< The X vector component of this Quaternion.
	float y; //!< The Y vector component of this Quaternion.
	float z; //!< The Z vector component of this Quaternion.

	Quaternion();
	Quaternion(float w, float x, float y, float z);
	Quaternion & operator*=( float s );
	Quaternion operator*( float s );
	Quaternion & operator+=( Quaternion src );
	Quaternion operator+( Quaternion src );
	float DotProduct( Quaternion src );
	Matrix33f AsMatrix();
	Vector3f AsEulerYawPitchRoll();
	Quaternion Inverse();
	void fromAxisAngle( Vector3f axis, float angle );
	void toAxisAngle( Vector3f& axis, float &angle );
	float& operator[]( unsigned int i );

	void Normalize();
	Quaternion Slerp (float t, Quaternion& src);
};

extern "C" struct TexCoord2f {
	float u;
	float v;
};

extern "C" struct TexCoord3f {
	float u;
	float v;
	float w;
};

extern "C" struct Matrix22f {
	float m[2][2];
//	static const Matrix22f IDENTITY;
	Matrix22f();
	Matrix22f(
		float m11, float m12,
		float m21, float m22
	);
	Matrix22f Inverse();
	Matrix22f operator + (Matrix22f src);
	Matrix22f operator - (Matrix22f src);
	Matrix22f operator * (Matrix22f src);
	Matrix22f operator * (float src);
//	Matrix22f& operator = (Matrix22f& src);

};

extern "C" struct Matrix33f {
	float m[3][3];
//	static Matrix33f Identity();
	Matrix33f();
	Matrix33f(
		float m11, float m12, float m13,
		float m21, float m22, float m23,
		float m31, float m32, float m33);
	Matrix33f(Vector3f v0, Vector3f v1, Vector3f v2);
	Matrix33f operator + (Matrix33f src);
	Matrix33f operator - (Matrix33f src);
	Matrix33f operator * (Matrix33f src);
	Vector3f operator *(Vector3f v);
	Matrix33f operator * (float scale);
//	Matrix33f& operator = (Matrix33f& src);
	Matrix33f Rotate(Vector3f normal, float angle);
//	Matrix33f Identity();
//	Matrix33f Invert();
	Matrix33f Transpose();
	Quaternion AsQuaternion();
	float Determinant();

	void fromQuat(Quaternion &src);
	Quaternion toQuat();
	
	void fromEuler( float x, float y, float z );
	BOOL8 toEuler( float &x, float &y, float &z );
};

extern "C" struct Matrix44f {
	float m[4][4];
//	static Matrix44f Identity();
	Matrix44f(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44
	);
//	Matrix44f( const Vector3f & translate, const Matrix33f & rotation, float scale );
//	Matrix44f( const Matrix33f & rotation );
	Matrix44f( const Vector3f &translation, const Matrix33f &rotation );
	Matrix44f();

	Matrix44f operator + (Matrix44f src);
	Matrix44f operator - (Matrix44f src);
	Matrix44f operator * (Matrix44f src);
	Matrix44f operator * (float scale);
//	Matrix44f& operator = (Matrix44f& src);
	Matrix44f& operator *= (Matrix44f src);
	Matrix44f& operator *= (float scale);
	Matrix44f& operator += (Matrix44f src);
	Matrix44f& operator -= (Matrix44f src);
	Matrix44f Rotate(Vector3f normal, float angle);
	Matrix44f Inverse();
	Matrix44f Transpose();
	float Determinant();
	Matrix33f Submatrix( int skip_r, int skip_c );
	float Adjoint( int skip_r, int skip_c );
	Matrix33f GetRotation();
	float GetScale();
	Vector3f GetTranslation();
	void Decompose( Vector3f &translate, Matrix33f &rotation, float &scale );
	void Decompose( Vector3f &trans, Matrix33f &rot, Vector3f &scale );
	void Compose( Vector3f &trans, Matrix33f &rot, Vector3f &scale );
	Vector4f operator * (Vector4f& src);
	Vector3f operator * (Vector3f& src);
	float MultiZ(Vector4f& src);
	float MultiZ(Vector3f& src);
};

extern "C" struct Matrix34f {
	float m[3][4];
//	static Matrix34f Identity();
	Matrix34f();
	Matrix34f(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34
		);
	Matrix34f(Matrix33f rotation );

	Matrix34f operator*(Matrix34f src);
	Matrix34f & operator*=(Matrix34f src);
	Matrix34f operator*( float scale);
	Matrix34f & operator*=( float scale);
	Vector3f operator*(Vector3f src);
	Matrix34f operator+(Matrix34f src);
	Matrix34f & operator+=(Matrix34f src);
//	Matrix34f & operator=(Matrix34f &src);
	//bool operator==( const InertiaMatrix & rh ) const;
	//bool operator!=( const InertiaMatrix & rh ) const;

	Matrix34f Transpose();
	float Determinant() ;
	Matrix34f Inverse();
	Matrix33f Submatrix( int skip_r, int skip_c );
	float Adjoint( int skip_r, int skip_c );
};

extern "C" struct Transform {
	Matrix33f rotation;
	Vector3f translation;
	float scale;

	Transform();
	Transform(Vector3f trans, Matrix33f rot, float scale);
	Transform Inverse();
	Transform operator*( Transform src);
	Vector3f operator*( Vector3f src);
	Matrix44f toMatrix4();

};

#endif