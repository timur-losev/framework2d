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
	${OBJECTDIR}/MainWindow.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/moc_MainWindow.o \
	${OBJECTDIR}/moc_QIrrControl.o \
	${OBJECTDIR}/QIrrControl.o


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
LDLIBSOPTIONS=-lQtCore -lQtGui ../../lib/irres/lib/Linux/libIrrlicht.a -lGL -lXxf86vm -lgdk-x11-2.0

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qtcontroll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qtcontroll: ../../lib/irres/lib/Linux/libIrrlicht.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qtcontroll: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qtcontroll ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/MainWindow.o: MainWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I../../lib/irres/include -I/usr/include/qt4 -I/usr/include/gtk-2.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/atk-1.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/MainWindow.o MainWindow.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I../../lib/irres/include -I/usr/include/qt4 -I/usr/include/gtk-2.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/atk-1.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/moc_MainWindow.o: moc_MainWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I../../lib/irres/include -I/usr/include/qt4 -I/usr/include/gtk-2.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/atk-1.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/moc_MainWindow.o moc_MainWindow.cpp

${OBJECTDIR}/moc_QIrrControl.o: moc_QIrrControl.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I../../lib/irres/include -I/usr/include/qt4 -I/usr/include/gtk-2.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/atk-1.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/moc_QIrrControl.o moc_QIrrControl.cpp

${OBJECTDIR}/QIrrControl.o: QIrrControl.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I../../lib/irres/include -I/usr/include/qt4 -I/usr/include/gtk-2.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/atk-1.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I. -std=c++11 -MMD -MP -MF $@.d -o ${OBJECTDIR}/QIrrControl.o QIrrControl.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qtcontroll

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
