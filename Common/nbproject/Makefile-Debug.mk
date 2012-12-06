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
CND_PLATFORM=GNU_SNAP-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Source/BoundedBufferReader.o \
	${OBJECTDIR}/Source/AppApi.o \
	${OBJECTDIR}/Source/MemoryStream.o \
	${OBJECTDIR}/Source/SigSlot2.o \
	${OBJECTDIR}/Source/DynamicMemoryStream.o \
	${OBJECTDIR}/pch.o \
	${OBJECTDIR}/Source/Invoker.o \
	${OBJECTDIR}/Source/MemoryStreamExceptions.o \
	${OBJECTDIR}/Source/FileStream.o \
	${OBJECTDIR}/Source/Logger.o \
	${OBJECTDIR}/Source/Common.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/../../_lib/${CND_CONF}/${CND_PLATFORM}/libcommon.a

${CND_DISTDIR}/../../_lib/${CND_CONF}/${CND_PLATFORM}/libcommon.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/../../_lib/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/../../_lib/${CND_CONF}/${CND_PLATFORM}/libcommon.a
	${AR} -rv ${CND_DISTDIR}/../../_lib/${CND_CONF}/${CND_PLATFORM}/libcommon.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/../../_lib/${CND_CONF}/${CND_PLATFORM}/libcommon.a

${OBJECTDIR}/Source/BoundedBufferReader.o: Source/BoundedBufferReader.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -IInclude -ISource -I. -I../../boost -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/BoundedBufferReader.o Source/BoundedBufferReader.cpp

${OBJECTDIR}/Source/AppApi.o: Source/AppApi.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -IInclude -ISource -I. -I../../boost -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/AppApi.o Source/AppApi.cpp

${OBJECTDIR}/Source/MemoryStream.o: Source/MemoryStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -IInclude -ISource -I. -I../../boost -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/MemoryStream.o Source/MemoryStream.cpp

${OBJECTDIR}/Source/SigSlot2.o: Source/SigSlot2.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -IInclude -ISource -I. -I../../boost -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/SigSlot2.o Source/SigSlot2.cpp

${OBJECTDIR}/Source/DynamicMemoryStream.o: Source/DynamicMemoryStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -IInclude -ISource -I. -I../../boost -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/DynamicMemoryStream.o Source/DynamicMemoryStream.cpp

${OBJECTDIR}/pch.o: pch.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -IInclude -ISource -I. -I../../boost -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/pch.o pch.cpp

${OBJECTDIR}/Source/Invoker.o: Source/Invoker.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -IInclude -ISource -I. -I../../boost -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/Invoker.o Source/Invoker.cpp

${OBJECTDIR}/Source/MemoryStreamExceptions.o: Source/MemoryStreamExceptions.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -IInclude -ISource -I. -I../../boost -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/MemoryStreamExceptions.o Source/MemoryStreamExceptions.cpp

${OBJECTDIR}/Source/FileStream.o: Source/FileStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -IInclude -ISource -I. -I../../boost -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/FileStream.o Source/FileStream.cpp

${OBJECTDIR}/Source/Logger.o: Source/Logger.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -IInclude -ISource -I. -I../../boost -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/Logger.o Source/Logger.cpp

${OBJECTDIR}/Source/Common.o: Source/Common.cpp 
	${MKDIR} -p ${OBJECTDIR}/Source
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -IInclude -ISource -I. -I../../boost -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Source/Common.o Source/Common.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/../../_lib/${CND_CONF}/${CND_PLATFORM}/libcommon.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
