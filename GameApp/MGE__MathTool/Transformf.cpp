///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _MATHTOOL_EXPORT

#include "../MGE_Base/Type.h"
#include "../MGE__MathTool/MathTool.h"
#include "string.h"


Vector3f Transform::operator*( Vector3f src) {
	return rotation * src * scale + translation;
}

Transform Transform::operator*( Transform src) {
	Transform t;
	t.rotation = rotation * src.rotation;
	t.translation = translation + rotation * src.translation * scale;
	t.scale = scale * src.scale;
	return t;
}
	
Transform::Transform() {
	scale = 1.0f;
}

Transform::Transform(Vector3f trans, Matrix33f rot, float s) {
	translation = trans;
	rotation = rot;
	scale = s;

}

Transform Transform::Inverse() {
	Matrix44f itrans(translation * -1.0f, Matrix33f());
	Matrix44f irot(Vector3f(), rotation.Transpose()); 
	Matrix44f imat = irot * itrans;
	return Transform(imat.GetTranslation(), imat.GetRotation(), 1.0f);
}

Matrix44f Transform::toMatrix4() {
	Matrix44f m44;
	for ( int c = 0; c < 3; c++ ) {
		for ( int d = 0; d < 3; d++ ) {
			m44.m[c][d] = rotation.m[c][d] * scale;
		}
		m44.m[3][c] = translation[c];
	}
	m44.m[3][0] = 0.0f;
	m44.m[3][1] = 0.0f;
	m44.m[3][2] = 0.0f;
	m44.m[3][3] = 1.0f;
	return m44;

}

