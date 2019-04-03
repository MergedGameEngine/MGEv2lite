///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

#define _BASE_IMPORT
#define _MATHTOOL_IMPORT
#define _RENDERER_EXPORT

#include "string.h"
#undef GetClassName
//#include "..\Base\Type.h"
//#include "..\Base\Base.h"
#undef _ARRAY_API
#define _ARRAY_API _RENDERER_API
#include "GLRendererObject.hpp"

#include "GLTextureObject.hpp"
#include "GLMeshObject.hpp"
#include "GLShaderObject.hpp"
#include "GLParameter.hpp"
//#include "ShaderParameter.hpp"

MGE2GLRendererObject::MGE2GLRendererObject() {
}

MGE2GLRendererObject::~MGE2GLRendererObject() {
}

const char *MGE2GLRendererObject::GetClassName() {
	return "MGE2GLRendererObject";
}

BOOL32 MGE2GLRendererObject::IsInstanceof(const char* className) {
	if (strcmp("MGE2GLRendererObject", className) == 0) {
		return TRUE;
	}
	return FALSE;
}

void MGE2GLRendererObject::RenderUnit() {
	unsigned int numeshes = MGE2RendererObject::meshes.GetLength();
	MGE2GLTextureObject *to = NULL;
	MGE2GLMeshObject *mo = NULL;
	MGE2GLShaderObject *so = NULL;
	MGE2Parameter *param = NULL;///<<===External Parameters, not shader's internal parameters

	for ( unsigned int i1 = 0 ; i1 < numeshes ; i1 ++ ) {
		mo = (MGE2GLMeshObject*)&meshes[i1];
		if ( mo == NULL ) {
			return;
		}
		so = (MGE2GLShaderObject*)shaderIndex.Get(mo->shaderName);
		if ( so == NULL ) {
			MGE2GLShaderObject::UnuseProgram();
			//return;
		} else {
			so->UseProgram();
		}
		unsigned int numtextures = mo->textureNames.GetLength();
		for ( unsigned int i2 = 0 ; i2 < numtextures ; i2 ++ ) {
			to = (MGE2GLTextureObject*)textureIndex.Get(mo->textureNames[i2]);
			if ( to != NULL ) {
				to->ActiveTexture();
				to->BindTexture();
				so->SetParameter(to->typeName, to->GetIndex());
			}
		}
		///tc.ActiveTexture0();
		glActiveTexture(GL_TEXTURE0);

		if ( so != NULL ) {
			param = (MGE2Parameter*)parameterIndex.Get(mo->shaderName);
			if ( param != NULL ) {
				MGE2Variant &_pv = param->vParameter;
				unsigned int numparam = _pv["numparam"].GetUInt(NULL);
				MGE2Variant &_pvv = _pv["params"];
				for ( unsigned int i3 = 0 ; i3 < numparam ; i3 ++ ) {
					MGEString __key;
					_pvv[i3]["key"].Copy2String(__key);
					so->SetParameter(__key, _pvv[i3]);
				}
			}
		}



///		so->SetParameter(vp.imvParamName, 1, GL_FALSE, &vp.invertModelView);
		if ( ( mo->GetBoneMatricesBuffer() != NULL ) && ( so != NULL ) ) {
			so->SetParameter(mo->boneMatrixParamName, mo->GetNumBoneMatrices(), TRUE, mo->GetBoneMatricesBuffer());
		}
//======
	///	glEnableVertexAttribArray(vertexAttrib);
	///	glEnableVertexAttribArray(normalAttrib);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		if ( ( mo->HasTangents() ) &&  ( so != NULL ) ) {
			so->EnableVertexAttribArray(mo->tangentParamName);
		}
		if ( ( mo->HasBinormals() ) && ( so != NULL ) ) {
			so->EnableVertexAttribArray(mo->binormalParamName);
		}
		if ( so != NULL ) {
			so->EnableVertexAttribArray(mo->texCoordParamName);
		}
		if ( ( mo->HasBoneIndices() ) && ( so != NULL ) ) {
			so->EnableVertexAttribArray(mo->boneIndexParamName);
		}
		if ( ( mo->HasWeights() ) && ( so != NULL ) ) {
			so->EnableVertexAttribArray(mo->vertexWeightParamName);
		}

		mo->BindVerticesBuffer();
		glVertexPointer(3, GL_FLOAT, 0, 0);
		///glVertexAttribPointer(vertexAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

		mo->BindNormalsBuffer();
		glNormalPointer(GL_FLOAT, 0, 0);
		///glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

		if ( mo->HasTangents() ) {
			mo->BindTangentsBuffer();
			so->SetParameter(mo->tangentParamName, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		}

		if ( mo->HasBinormals() ) {
			mo->BindBinormalsBuffer();
			so->SetParameter(mo->binormalParamName, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		}

		if ( so != NULL ) {
			// Texture coordinates
			mo->BindTexCoordsBuffer();
			so->SetParameter(mo->texCoordParamName, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		}

		// Bone Indices
		if ( ( mo->HasBoneIndices() ) && ( so != NULL ) ) {
			mo->BindBoneIndicesBuffer();
			so->SetParameter(mo->boneIndexParamName, 4, GL_UNSIGNED_SHORT, GL_FALSE, 0, NULL);
		}
		// Vertex Weights
		if ( ( mo->HasWeights() ) && ( so != NULL ) ) {
			mo->BindVertexWeightsBuffer();
			so->SetParameter(mo->vertexWeightParamName, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		}
		// Indexes
		mo->BindIndicesBuffer();
	///	glDrawArrays(GL_TRIANGLES, 0, bodyData->GetNumTriangles() * 3);
	///	glDrawElements(GL_TRIANGLES, bodyData->GetNumTriangles() * 3, GL_UNSIGNED_SHORT, 0);
		glDrawElements(GL_TRIANGLES, mo->GetNumIndices(), GL_UNSIGNED_SHORT, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	///	glDisableVertexAttribArray(vertexAttrib);
	///	glDisableVertexAttribArray(normalAttrib);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		if ( ( mo->HasTangents() ) && ( so != NULL ) ) {
			so->DisableVertexAttribArray(mo->tangentParamName);
		}
		if ( ( mo->HasBinormals() ) && ( so != NULL ) ) {
			so->DisableVertexAttribArray(mo->binormalParamName);
		}
		if ( so != NULL ) {
			so->DisableVertexAttribArray(mo->texCoordParamName);
		}
		if ( ( mo->HasBoneIndices() ) && ( so != NULL ) ) {
			so->DisableVertexAttribArray(mo->boneIndexParamName);
		}
		if ( ( mo->HasWeights() ) && ( so != NULL ) ) {
			so->DisableVertexAttribArray(mo->vertexWeightParamName);
		}

//======
		MGE2GLShaderObject::UnuseProgram();
	}
}
