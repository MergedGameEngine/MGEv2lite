#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/GameApp.o \
	${OBJECTDIR}/MGE_Base/Array.o \
	${OBJECTDIR}/MGE_Base/CRC32.o \
	${OBJECTDIR}/MGE_Base/Hashtable.o \
	${OBJECTDIR}/MGE_Base/ObjectArray.o \
	${OBJECTDIR}/MGE_Base/RefArray.o \
	${OBJECTDIR}/MGE_Base/String.o \
	${OBJECTDIR}/MGE_Base/String16.o \
	${OBJECTDIR}/MGE_Base/Variant.o \
	${OBJECTDIR}/MGE_Base/WString.o \
	${OBJECTDIR}/MGE_File/File.o \
	${OBJECTDIR}/MGE_File/FileStream.o \
	${OBJECTDIR}/MGE_Network/Client.o \
	${OBJECTDIR}/MGE_Network/ClientHandler.o \
	${OBJECTDIR}/MGE_Network/Network.o \
	${OBJECTDIR}/MGE_Network/Server.o \
	${OBJECTDIR}/MGE_Network/TSocket.o \
	${OBJECTDIR}/MGE_Thread/Barrier.o \
	${OBJECTDIR}/MGE_Thread/Condition.o \
	${OBJECTDIR}/MGE_Thread/Lock.o \
	${OBJECTDIR}/MGE_Thread/Mutex.o \
	${OBJECTDIR}/MGE_Thread/RWLock.o \
	${OBJECTDIR}/MGE_Thread/Semaphore.o \
	${OBJECTDIR}/MGE_Thread/SpinLock.o \
	${OBJECTDIR}/MGE_Thread/Thread.o \
	${OBJECTDIR}/MGE__Config/Config.o \
	${OBJECTDIR}/MGE__Config/ConfigFile.o \
	${OBJECTDIR}/MGE__MathTool/MathTool.o \
	${OBJECTDIR}/MGE__MathTool/Matrix22f.o \
	${OBJECTDIR}/MGE__MathTool/Matrix33f.o \
	${OBJECTDIR}/MGE__MathTool/Matrix34f.o \
	${OBJECTDIR}/MGE__MathTool/Matrix44f.o \
	${OBJECTDIR}/MGE__MathTool/Quaternionf.o \
	${OBJECTDIR}/MGE__MathTool/TexCoord2f.o \
	${OBJECTDIR}/MGE__MathTool/Transformf.o \
	${OBJECTDIR}/MGE__MathTool/Triangle.o \
	${OBJECTDIR}/MGE__MathTool/Vector3f.o \
	${OBJECTDIR}/MGE__MathTool/Vector4f.o \
	${OBJECTDIR}/MGE__ModelData/Bone.o \
	${OBJECTDIR}/MGE__ModelData/BoneController.o \
	${OBJECTDIR}/MGE__ModelData/BoneTreeNode.o \
	${OBJECTDIR}/MGE__ModelData/CollisionDetectingMatrices.o \
	${OBJECTDIR}/MGE__ModelData/CollisionDetectingMatricesController.o \
	${OBJECTDIR}/MGE__ModelData/DDSTexture.o \
	${OBJECTDIR}/MGE__ModelData/KeyFrame.o \
	${OBJECTDIR}/MGE__ModelData/Mesh.o \
	${OBJECTDIR}/MGE__ModelData/Model.o \
	${OBJECTDIR}/MGE__ModelData/ModelPack.o \
	${OBJECTDIR}/MGE__ModelData/Sequence.o \
	${OBJECTDIR}/MGE__ModelData/Surface.o \
	${OBJECTDIR}/MGE__ModelData/TGATexture.o \
	${OBJECTDIR}/MGE__ModelData/Texture.o \
	${OBJECTDIR}/MGEv2__GLRenderer/GLFrameObject.o \
	${OBJECTDIR}/MGEv2__GLRenderer/GLMeshObject.o \
	${OBJECTDIR}/MGEv2__GLRenderer/GLParameter.o \
	${OBJECTDIR}/MGEv2__GLRenderer/GLRendererContext.o \
	${OBJECTDIR}/MGEv2__GLRenderer/GLRendererObject.o \
	${OBJECTDIR}/MGEv2__GLRenderer/GLShaderObject.o \
	${OBJECTDIR}/MGEv2__GLRenderer/GLTextureObject.o \
	${OBJECTDIR}/MGEv2__Game/Core.o \
	${OBJECTDIR}/MGEv2__Game/GameObject.o \
	${OBJECTDIR}/MGEv2__Game/InterfaceVFrameObject.o \
	${OBJECTDIR}/MGEv2__Game/InterfaceVMeshObject.o \
	${OBJECTDIR}/MGEv2__Game/InterfaceVParameter.o \
	${OBJECTDIR}/MGEv2__Game/InterfaceVRendererContext.o \
	${OBJECTDIR}/MGEv2__Game/InterfaceVRendererObject.o \
	${OBJECTDIR}/MGEv2__Game/InterfaceVShaderObject.o \
	${OBJECTDIR}/MGEv2__Game/InterfaceVTextureObject.o \
	${OBJECTDIR}/MGEv2__Game/MessageProc.o \
	${OBJECTDIR}/MGEv2__Game/Sandbox.o \
	${OBJECTDIR}/_MGEv1_Test/RendererOutput.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs gl` `pkg-config --libs glew` -lpthread  `pkg-config --libs x11`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/GameApp

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/GameApp: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/GameApp ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/GameApp.o: GameApp.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GameApp.o GameApp.cpp

${OBJECTDIR}/MGE_Base/Array.o: MGE_Base/Array.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Base
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Base/Array.o MGE_Base/Array.cpp

${OBJECTDIR}/MGE_Base/CRC32.o: MGE_Base/CRC32.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Base
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Base/CRC32.o MGE_Base/CRC32.cpp

${OBJECTDIR}/MGE_Base/Hashtable.o: MGE_Base/Hashtable.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Base
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Base/Hashtable.o MGE_Base/Hashtable.cpp

${OBJECTDIR}/MGE_Base/ObjectArray.o: MGE_Base/ObjectArray.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Base
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Base/ObjectArray.o MGE_Base/ObjectArray.cpp

${OBJECTDIR}/MGE_Base/RefArray.o: MGE_Base/RefArray.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Base
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Base/RefArray.o MGE_Base/RefArray.cpp

${OBJECTDIR}/MGE_Base/String.o: MGE_Base/String.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Base
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Base/String.o MGE_Base/String.cpp

${OBJECTDIR}/MGE_Base/String16.o: MGE_Base/String16.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Base
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Base/String16.o MGE_Base/String16.cpp

${OBJECTDIR}/MGE_Base/Variant.o: MGE_Base/Variant.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Base
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Base/Variant.o MGE_Base/Variant.cpp

${OBJECTDIR}/MGE_Base/WString.o: MGE_Base/WString.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Base
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Base/WString.o MGE_Base/WString.cpp

${OBJECTDIR}/MGE_File/File.o: MGE_File/File.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_File
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_File/File.o MGE_File/File.cpp

${OBJECTDIR}/MGE_File/FileStream.o: MGE_File/FileStream.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_File
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_File/FileStream.o MGE_File/FileStream.cpp

${OBJECTDIR}/MGE_Network/Client.o: MGE_Network/Client.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Network
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Network/Client.o MGE_Network/Client.cpp

${OBJECTDIR}/MGE_Network/ClientHandler.o: MGE_Network/ClientHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Network
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Network/ClientHandler.o MGE_Network/ClientHandler.cpp

${OBJECTDIR}/MGE_Network/Network.o: MGE_Network/Network.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Network
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Network/Network.o MGE_Network/Network.cpp

${OBJECTDIR}/MGE_Network/Server.o: MGE_Network/Server.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Network
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Network/Server.o MGE_Network/Server.cpp

${OBJECTDIR}/MGE_Network/TSocket.o: MGE_Network/TSocket.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Network
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Network/TSocket.o MGE_Network/TSocket.cpp

${OBJECTDIR}/MGE_Thread/Barrier.o: MGE_Thread/Barrier.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Thread
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Thread/Barrier.o MGE_Thread/Barrier.cpp

${OBJECTDIR}/MGE_Thread/Condition.o: MGE_Thread/Condition.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Thread
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Thread/Condition.o MGE_Thread/Condition.cpp

${OBJECTDIR}/MGE_Thread/Lock.o: MGE_Thread/Lock.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Thread
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Thread/Lock.o MGE_Thread/Lock.cpp

${OBJECTDIR}/MGE_Thread/Mutex.o: MGE_Thread/Mutex.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Thread
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Thread/Mutex.o MGE_Thread/Mutex.cpp

${OBJECTDIR}/MGE_Thread/RWLock.o: MGE_Thread/RWLock.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Thread
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Thread/RWLock.o MGE_Thread/RWLock.cpp

${OBJECTDIR}/MGE_Thread/Semaphore.o: MGE_Thread/Semaphore.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Thread
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Thread/Semaphore.o MGE_Thread/Semaphore.cpp

${OBJECTDIR}/MGE_Thread/SpinLock.o: MGE_Thread/SpinLock.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Thread
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Thread/SpinLock.o MGE_Thread/SpinLock.cpp

${OBJECTDIR}/MGE_Thread/Thread.o: MGE_Thread/Thread.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE_Thread
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE_Thread/Thread.o MGE_Thread/Thread.cpp

${OBJECTDIR}/MGE__Config/Config.o: MGE__Config/Config.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__Config
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__Config/Config.o MGE__Config/Config.cpp

${OBJECTDIR}/MGE__Config/ConfigFile.o: MGE__Config/ConfigFile.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__Config
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__Config/ConfigFile.o MGE__Config/ConfigFile.cpp

${OBJECTDIR}/MGE__MathTool/MathTool.o: MGE__MathTool/MathTool.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__MathTool
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__MathTool/MathTool.o MGE__MathTool/MathTool.cpp

${OBJECTDIR}/MGE__MathTool/Matrix22f.o: MGE__MathTool/Matrix22f.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__MathTool
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__MathTool/Matrix22f.o MGE__MathTool/Matrix22f.cpp

${OBJECTDIR}/MGE__MathTool/Matrix33f.o: MGE__MathTool/Matrix33f.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__MathTool
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__MathTool/Matrix33f.o MGE__MathTool/Matrix33f.cpp

${OBJECTDIR}/MGE__MathTool/Matrix34f.o: MGE__MathTool/Matrix34f.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__MathTool
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__MathTool/Matrix34f.o MGE__MathTool/Matrix34f.cpp

${OBJECTDIR}/MGE__MathTool/Matrix44f.o: MGE__MathTool/Matrix44f.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__MathTool
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__MathTool/Matrix44f.o MGE__MathTool/Matrix44f.cpp

${OBJECTDIR}/MGE__MathTool/Quaternionf.o: MGE__MathTool/Quaternionf.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__MathTool
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__MathTool/Quaternionf.o MGE__MathTool/Quaternionf.cpp

${OBJECTDIR}/MGE__MathTool/TexCoord2f.o: MGE__MathTool/TexCoord2f.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__MathTool
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__MathTool/TexCoord2f.o MGE__MathTool/TexCoord2f.cpp

${OBJECTDIR}/MGE__MathTool/Transformf.o: MGE__MathTool/Transformf.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__MathTool
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__MathTool/Transformf.o MGE__MathTool/Transformf.cpp

${OBJECTDIR}/MGE__MathTool/Triangle.o: MGE__MathTool/Triangle.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__MathTool
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__MathTool/Triangle.o MGE__MathTool/Triangle.cpp

${OBJECTDIR}/MGE__MathTool/Vector3f.o: MGE__MathTool/Vector3f.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__MathTool
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__MathTool/Vector3f.o MGE__MathTool/Vector3f.cpp

${OBJECTDIR}/MGE__MathTool/Vector4f.o: MGE__MathTool/Vector4f.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__MathTool
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__MathTool/Vector4f.o MGE__MathTool/Vector4f.cpp

${OBJECTDIR}/MGE__ModelData/Bone.o: MGE__ModelData/Bone.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__ModelData
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__ModelData/Bone.o MGE__ModelData/Bone.cpp

${OBJECTDIR}/MGE__ModelData/BoneController.o: MGE__ModelData/BoneController.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__ModelData
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__ModelData/BoneController.o MGE__ModelData/BoneController.cpp

${OBJECTDIR}/MGE__ModelData/BoneTreeNode.o: MGE__ModelData/BoneTreeNode.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__ModelData
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__ModelData/BoneTreeNode.o MGE__ModelData/BoneTreeNode.cpp

${OBJECTDIR}/MGE__ModelData/CollisionDetectingMatrices.o: MGE__ModelData/CollisionDetectingMatrices.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__ModelData
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__ModelData/CollisionDetectingMatrices.o MGE__ModelData/CollisionDetectingMatrices.cpp

${OBJECTDIR}/MGE__ModelData/CollisionDetectingMatricesController.o: MGE__ModelData/CollisionDetectingMatricesController.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__ModelData
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__ModelData/CollisionDetectingMatricesController.o MGE__ModelData/CollisionDetectingMatricesController.cpp

${OBJECTDIR}/MGE__ModelData/DDSTexture.o: MGE__ModelData/DDSTexture.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__ModelData
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__ModelData/DDSTexture.o MGE__ModelData/DDSTexture.cpp

${OBJECTDIR}/MGE__ModelData/KeyFrame.o: MGE__ModelData/KeyFrame.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__ModelData
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__ModelData/KeyFrame.o MGE__ModelData/KeyFrame.cpp

${OBJECTDIR}/MGE__ModelData/Mesh.o: MGE__ModelData/Mesh.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__ModelData
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__ModelData/Mesh.o MGE__ModelData/Mesh.cpp

${OBJECTDIR}/MGE__ModelData/Model.o: MGE__ModelData/Model.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__ModelData
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__ModelData/Model.o MGE__ModelData/Model.cpp

${OBJECTDIR}/MGE__ModelData/ModelPack.o: MGE__ModelData/ModelPack.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__ModelData
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__ModelData/ModelPack.o MGE__ModelData/ModelPack.cpp

${OBJECTDIR}/MGE__ModelData/Sequence.o: MGE__ModelData/Sequence.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__ModelData
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__ModelData/Sequence.o MGE__ModelData/Sequence.cpp

${OBJECTDIR}/MGE__ModelData/Surface.o: MGE__ModelData/Surface.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__ModelData
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__ModelData/Surface.o MGE__ModelData/Surface.cpp

${OBJECTDIR}/MGE__ModelData/TGATexture.o: MGE__ModelData/TGATexture.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__ModelData
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__ModelData/TGATexture.o MGE__ModelData/TGATexture.cpp

${OBJECTDIR}/MGE__ModelData/Texture.o: MGE__ModelData/Texture.cpp
	${MKDIR} -p ${OBJECTDIR}/MGE__ModelData
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGE__ModelData/Texture.o MGE__ModelData/Texture.cpp

${OBJECTDIR}/MGEv2__GLRenderer/GLFrameObject.o: MGEv2__GLRenderer/GLFrameObject.cpp
	${MKDIR} -p ${OBJECTDIR}/MGEv2__GLRenderer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGEv2__GLRenderer/GLFrameObject.o MGEv2__GLRenderer/GLFrameObject.cpp

${OBJECTDIR}/MGEv2__GLRenderer/GLMeshObject.o: MGEv2__GLRenderer/GLMeshObject.cpp
	${MKDIR} -p ${OBJECTDIR}/MGEv2__GLRenderer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGEv2__GLRenderer/GLMeshObject.o MGEv2__GLRenderer/GLMeshObject.cpp

${OBJECTDIR}/MGEv2__GLRenderer/GLParameter.o: MGEv2__GLRenderer/GLParameter.cpp
	${MKDIR} -p ${OBJECTDIR}/MGEv2__GLRenderer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGEv2__GLRenderer/GLParameter.o MGEv2__GLRenderer/GLParameter.cpp

${OBJECTDIR}/MGEv2__GLRenderer/GLRendererContext.o: MGEv2__GLRenderer/GLRendererContext.cpp
	${MKDIR} -p ${OBJECTDIR}/MGEv2__GLRenderer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGEv2__GLRenderer/GLRendererContext.o MGEv2__GLRenderer/GLRendererContext.cpp

${OBJECTDIR}/MGEv2__GLRenderer/GLRendererObject.o: MGEv2__GLRenderer/GLRendererObject.cpp
	${MKDIR} -p ${OBJECTDIR}/MGEv2__GLRenderer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGEv2__GLRenderer/GLRendererObject.o MGEv2__GLRenderer/GLRendererObject.cpp

${OBJECTDIR}/MGEv2__GLRenderer/GLShaderObject.o: MGEv2__GLRenderer/GLShaderObject.cpp
	${MKDIR} -p ${OBJECTDIR}/MGEv2__GLRenderer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGEv2__GLRenderer/GLShaderObject.o MGEv2__GLRenderer/GLShaderObject.cpp

${OBJECTDIR}/MGEv2__GLRenderer/GLTextureObject.o: MGEv2__GLRenderer/GLTextureObject.cpp
	${MKDIR} -p ${OBJECTDIR}/MGEv2__GLRenderer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGEv2__GLRenderer/GLTextureObject.o MGEv2__GLRenderer/GLTextureObject.cpp

${OBJECTDIR}/MGEv2__Game/Core.o: MGEv2__Game/Core.cpp
	${MKDIR} -p ${OBJECTDIR}/MGEv2__Game
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGEv2__Game/Core.o MGEv2__Game/Core.cpp

${OBJECTDIR}/MGEv2__Game/GameObject.o: MGEv2__Game/GameObject.cpp
	${MKDIR} -p ${OBJECTDIR}/MGEv2__Game
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGEv2__Game/GameObject.o MGEv2__Game/GameObject.cpp

${OBJECTDIR}/MGEv2__Game/InterfaceVFrameObject.o: MGEv2__Game/InterfaceVFrameObject.cpp
	${MKDIR} -p ${OBJECTDIR}/MGEv2__Game
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGEv2__Game/InterfaceVFrameObject.o MGEv2__Game/InterfaceVFrameObject.cpp

${OBJECTDIR}/MGEv2__Game/InterfaceVMeshObject.o: MGEv2__Game/InterfaceVMeshObject.cpp
	${MKDIR} -p ${OBJECTDIR}/MGEv2__Game
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGEv2__Game/InterfaceVMeshObject.o MGEv2__Game/InterfaceVMeshObject.cpp

${OBJECTDIR}/MGEv2__Game/InterfaceVParameter.o: MGEv2__Game/InterfaceVParameter.cpp
	${MKDIR} -p ${OBJECTDIR}/MGEv2__Game
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGEv2__Game/InterfaceVParameter.o MGEv2__Game/InterfaceVParameter.cpp

${OBJECTDIR}/MGEv2__Game/InterfaceVRendererContext.o: MGEv2__Game/InterfaceVRendererContext.cpp
	${MKDIR} -p ${OBJECTDIR}/MGEv2__Game
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGEv2__Game/InterfaceVRendererContext.o MGEv2__Game/InterfaceVRendererContext.cpp

${OBJECTDIR}/MGEv2__Game/InterfaceVRendererObject.o: MGEv2__Game/InterfaceVRendererObject.cpp
	${MKDIR} -p ${OBJECTDIR}/MGEv2__Game
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGEv2__Game/InterfaceVRendererObject.o MGEv2__Game/InterfaceVRendererObject.cpp

${OBJECTDIR}/MGEv2__Game/InterfaceVShaderObject.o: MGEv2__Game/InterfaceVShaderObject.cpp
	${MKDIR} -p ${OBJECTDIR}/MGEv2__Game
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGEv2__Game/InterfaceVShaderObject.o MGEv2__Game/InterfaceVShaderObject.cpp

${OBJECTDIR}/MGEv2__Game/InterfaceVTextureObject.o: MGEv2__Game/InterfaceVTextureObject.cpp
	${MKDIR} -p ${OBJECTDIR}/MGEv2__Game
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGEv2__Game/InterfaceVTextureObject.o MGEv2__Game/InterfaceVTextureObject.cpp

${OBJECTDIR}/MGEv2__Game/MessageProc.o: MGEv2__Game/MessageProc.cpp
	${MKDIR} -p ${OBJECTDIR}/MGEv2__Game
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGEv2__Game/MessageProc.o MGEv2__Game/MessageProc.cpp

${OBJECTDIR}/MGEv2__Game/Sandbox.o: MGEv2__Game/Sandbox.cpp
	${MKDIR} -p ${OBJECTDIR}/MGEv2__Game
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MGEv2__Game/Sandbox.o MGEv2__Game/Sandbox.cpp

${OBJECTDIR}/_MGEv1_Test/RendererOutput.o: _MGEv1_Test/RendererOutput.cpp
	${MKDIR} -p ${OBJECTDIR}/_MGEv1_Test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags gl` `pkg-config --cflags glew` `pkg-config --cflags x11`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_MGEv1_Test/RendererOutput.o _MGEv1_Test/RendererOutput.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
