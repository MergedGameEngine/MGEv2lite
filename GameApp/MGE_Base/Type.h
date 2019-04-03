///////////////////////////////////////////////////////////////////
//
//		Merged GameEngine (MGE)		Copyright 2009
//		All Rights Reserved
//		Author:		chen. Wang,
//
///////////////////////////////////////////////////////////////////

//
//	Definitions &
//	Macros
//

#ifndef _TYPE_H_
#define _TYPE_H_


typedef class MGEString _string;
#ifdef WIN32
typedef class MGETString _wstring;
#else
typedef class MGEWString _wstring;
#endif

typedef class MGE2Variant _var;


#define _LOCAL_ENDIAN_ MGEIOStream::little_endian

#define _0	(unsigned int)0 

typedef bool BOOL32;
typedef bool BOOL8;
#ifndef byte
typedef unsigned char byte;
#endif

#ifndef TRUE
#define TRUE true
#endif
#ifndef FALSE
#define FALSE false
#endif

#ifndef NULL
#define NULL 0
#endif

#define VARRETURN(x) x.SetReturn();return x;

/////////////////////////////////////////////////

//	.Base Package Classes
#define CLSID_TString				5
#define CLSID_THashtable			6
#define CLSID_TArray				7
#define CLSID_TRefArray				8
#define CLSID_TObjectArray			9

//	.Network Package Classes
#define	CLSID_TNetworkIOStream		192
#define	CLSID_TPacket				193
#define	CLSID_TServer				194
#define	CLSID_TServerHandler		195
#define	CLSID_TClient				196
#define	CLSID_TClientHandler		197

//	.Thread Package Classes
#define	CLSID_TThread				256
#define CLSID_TSemaphore			257
#define CLSID_TRWLock				258
#define CLSID_TSpinLock				259
#define CLSID_TMutex				260
#define CLSID_TBarrier				261

//	.File Package Classes
#define CLSID_TFileIOStream			128
#define	CLSID_TFile					129
#define	CLSID_TConfig				150
#define	CLSID_TConfigFile			151

/////////////////////////////////////////////////



//	.Sound Package Classes
#define CLSID_TAudioDevice			400
#define CLSID_TWaveDataObject		401
#define CLSID_TWaveSourceObject		402
#define CLSID_TWaveSourceController	403




/////////////////////////////////////////////////////////////
//
//		Renderer Input:
//		1) Shader		<<=== Renderer Object
//		2) Texture      <<=== Renderer Object
//		3) Material     <<=== Renderer Object, Shader Instance & Texture Instance
//		4) Mesh         <<=== Renderer Object
//		5) Parameter    <<=== from GameObject to Shader
//
//		Renderer Key Process:
//		1) LightingProcess
//		2) ShadowProcess
//
//		Renderer Output & Re-Input
//		1) Frame		<=== Renderer Object
//
/////////////////////////////////////////////////////////////


//	.Model Package Classes
#define CLSID_TModelObject			1024
#define CLSID_TMesh					1025
#define CLSID_TSkin					1026
#define CLSID_TBone					1027
#define CLSID_TBoneController		1028		
#define CLSID_TBoneTreeNode			1029

#define CLSID_TSequence				1030
#define CLSID_TKeyFrame				1031

#define CLSID_TCollisionDetectingMatrices				1050
#define CLSID_TCollisionDetectingMatricesController		1051
#define CLSID_TModel				1100
#define CLSID_TModelGlobal			1101

#define CLSID_TTexture				1200
#define CLSID_TTGATexture			1201
#define CLSID_TDDSTexture			1202


//	.Renderer Package Classes
#define CLSID_TViewPort				2048
#define CLSID_TViewPortController	2049
#define CLSID_TLightObject			2050
#define CLSID_TLightController		2051
#define	CLSID_TVertexObject			2052
#define CLSID_TMeshObject			2053
#define CLSID_TMeshController		2054
#define CLSID_TShaderParameter		2055
#define CLSID_TShaderObject			2056
#define CLSID_TShaderController		2057
#define CLSID_TTextureObject		2058
#define CLSID_TTextureController	2059
#define CLSID_TMultiTexture			2060
#define CLSID_TRenderBufferObject	2061
#define CLSID_TFrameObject			2062
#define CLSID_TFrameController		2063
#define	CLSID_TRenderingTaskController	2064
#define	CLSID_TRenderingTaskTreeNode	2065

/////////////////////////////////////////////////////////////
//
//		Game Input:
//		1) Model		<<=== Game Object, Renderer Object Instance
//		2) Sandbox      <<=== Game Object, Model Unique
//		3) Character	<<=== Game Object, Model Instance
//		4) Control		<<=== Game Object, including collision detect, clip control?
//
//		Game Key Process:
//		1) Event Process	<<=== Script
//		2) AI ?
//
//		Game Output & Re-Input
//		1) Feedback		<<=== Game Object
//
/////////////////////////////////////////////////////////////
//	.Core Package Classes
#define	CLSID_TCore					4096
#define	CLSID_TModelController		4097
#define	CLSID_TAnimationController	4098
#define CLSID_TAnimator				4099
#define	CLSID_TCharacter			4100
#define	CLSID_TNPC					4101
#define	CLSID_TPlayer				4102
#define	CLSID_TDevice				4103
#define	CLSID_TChest				4104
#define	CLSID_TWeapon				4105
#define	CLSID_TEvent				4500
#define	CLSID_TEventProcessor		4501
#define	CLSID_TEventListener		4502
#define	CLSID_TEventFilter			4503
#define CLSID_TLevel				4600
#define	CLSID_TArea					4601
#define	CLSID_TSection				4602
#define CLSID_TWindow				4300

/////////////////////////////////////////////////////////////
//
//		User Input:
//		1) Input		<<=== Keyboard, Mouse, Joy, Touch
//		2) Input2		<<=== IMP
//
//		User Key Process:
//		1) Game Process	<<=== Application Run
//		2) 
//
//		User Output & Re-Input
//		1) Media
//		2)
//
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
//
//		Game Converter Input:
//		1) Data
//		2) 
//
//		Game Converter Key Process:
//		1) Compartibility
//		2) 
//
//		Game Converter Output & Re-Input
//		1) MGE v2 Data
//		2)
//
/////////////////////////////////////////////////////////////


#endif