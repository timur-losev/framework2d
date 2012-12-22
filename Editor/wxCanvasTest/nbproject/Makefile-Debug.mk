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
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/wxIrrlichtTest.o \
	${OBJECTDIR}/wxIrrlichtCanvas.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../lib/GLES1x/LinuxX64/Lib -L../../lib/wxWidgets/current_build/lib -Wl,-rpath /home/void/Documents/framework2d/lib/wxWidgets/current_build/lib/ ../../lib/irres/lib/Linux/libIrrlicht.a -lpthread -lGL ../../lib/GLES1x/LinuxX64/Lib/libGLES_CM64.so -lwx_base-2.9 -lwx_gtk2_adv-2.9 -lwx_gtk2_core-2.9 -lwx_gtk2_gl-2.9 -lwx_gtk2_qa-2.9

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/wxcanvastest

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/wxcanvastest: ../../lib/irres/lib/Linux/libIrrlicht.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/wxcanvastest: ../../lib/GLES1x/LinuxX64/Lib/libGLES_CM64.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/wxcanvastest: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/wxcanvastest ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/wxIrrlichtTest.o: wxIrrlichtTest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -D__WXDEBUG__ -D__WXGTK__ -I../../lib/irres/include -I../../lib/irres/source/Irrlicht -I../../lib/wxWidgets/include -I../../lib/boost -I. -I../../lib/wxWidgets/current_build/lib/wx/include/gtk2-ansi-2.9 -I/usr/include/gtk-2.0 -I/usr/include/gtk-2.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/atk-1.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/wxIrrlichtTest.o wxIrrlichtTest.cpp

${OBJECTDIR}/wxIrrlichtCanvas.o: wxIrrlichtCanvas.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -D__WXDEBUG__ -D__WXGTK__ -I../../lib/irres/include -I../../lib/irres/source/Irrlicht -I../../lib/wxWidgets/include -I../../lib/boost -I. -I../../lib/wxWidgets/current_build/lib/wx/include/gtk2-ansi-2.9 -I/usr/include/gtk-2.0 -I/usr/include/gtk-2.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/atk-1.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/wxIrrlichtCanvas.o wxIrrlichtCanvas.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/wxcanvastest

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
