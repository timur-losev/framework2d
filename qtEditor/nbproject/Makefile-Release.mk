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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Application.o \
	${OBJECTDIR}/Gui/AboutWindow.o \
	${OBJECTDIR}/_ext/2033245622/EditablePagedLevel.o \
	${OBJECTDIR}/_ext/2033245622/LevelFile.o \
	${OBJECTDIR}/GuiManager.o \
	${OBJECTDIR}/_ext/2033245622/GameObject.o \
	${OBJECTDIR}/Gui/MappingToolWindow.o \
	${OBJECTDIR}/_ext/1676536254/tinystr.o \
	${OBJECTDIR}/MappingToolLevel.o \
	${OBJECTDIR}/Gui/moc_QIrrControl.o \
	${OBJECTDIR}/AboutWindowController.o \
	${OBJECTDIR}/_ext/2033245622/ILevel.o \
	${OBJECTDIR}/_ext/1676536254/tinyxmlerror.o \
	${OBJECTDIR}/_ext/1676536254/tinyxmlparser.o \
	${OBJECTDIR}/Gui/moc_MappingToolWindow.o \
	${OBJECTDIR}/IrrWorker.o \
	${OBJECTDIR}/_ext/2033245622/ZwoptexParser.o \
	${OBJECTDIR}/_ext/1676536254/tinyxml.o \
	${OBJECTDIR}/Gui/MainWindow.o \
	${OBJECTDIR}/_ext/2033245622/StaticGameObject.o \
	${OBJECTDIR}/MapViewer.o \
	${OBJECTDIR}/_ext/2033245622/Sprite.o \
	${OBJECTDIR}/_ext/2033245622/MappingFile.o \
	${OBJECTDIR}/Gui/moc_MainWindow.o \
	${OBJECTDIR}/_ext/2033245622/Page.o \
	${OBJECTDIR}/Gui/QIrrControl.o \
	${OBJECTDIR}/MappingToolWindowController.o \
	${OBJECTDIR}/_ext/2033245622/AssetsManager.o \
	${OBJECTDIR}/_ext/2033245622/LevelManager.o \
	${OBJECTDIR}/MainWindowController.o \
	${OBJECTDIR}/_ext/2033245622/AnimatedGameObject.o \
	${OBJECTDIR}/Gui/moc_AboutWindow.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qteditor

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qteditor: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qteditor ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Application.o: Application.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Application.o Application.cpp

${OBJECTDIR}/Gui/AboutWindow.o: Gui/AboutWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/Gui
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Gui/AboutWindow.o Gui/AboutWindow.cpp

${OBJECTDIR}/_ext/2033245622/EditablePagedLevel.o: ../Game/Src/EditablePagedLevel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/EditablePagedLevel.o ../Game/Src/EditablePagedLevel.cpp

${OBJECTDIR}/_ext/2033245622/LevelFile.o: ../Game/Src/LevelFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/LevelFile.o ../Game/Src/LevelFile.cpp

${OBJECTDIR}/GuiManager.o: GuiManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/GuiManager.o GuiManager.cpp

${OBJECTDIR}/_ext/2033245622/GameObject.o: ../Game/Src/GameObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/GameObject.o ../Game/Src/GameObject.cpp

${OBJECTDIR}/Gui/MappingToolWindow.o: Gui/MappingToolWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/Gui
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Gui/MappingToolWindow.o Gui/MappingToolWindow.cpp

${OBJECTDIR}/_ext/1676536254/tinystr.o: ../lib/tinyxml/tinystr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1676536254
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1676536254/tinystr.o ../lib/tinyxml/tinystr.cpp

${OBJECTDIR}/MappingToolLevel.o: MappingToolLevel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/MappingToolLevel.o MappingToolLevel.cpp

${OBJECTDIR}/Gui/moc_QIrrControl.o: Gui/moc_QIrrControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/Gui
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Gui/moc_QIrrControl.o Gui/moc_QIrrControl.cpp

${OBJECTDIR}/AboutWindowController.o: AboutWindowController.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/AboutWindowController.o AboutWindowController.cpp

${OBJECTDIR}/_ext/2033245622/ILevel.o: ../Game/Src/ILevel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/ILevel.o ../Game/Src/ILevel.cpp

${OBJECTDIR}/_ext/1676536254/tinyxmlerror.o: ../lib/tinyxml/tinyxmlerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1676536254
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1676536254/tinyxmlerror.o ../lib/tinyxml/tinyxmlerror.cpp

${OBJECTDIR}/_ext/1676536254/tinyxmlparser.o: ../lib/tinyxml/tinyxmlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1676536254
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1676536254/tinyxmlparser.o ../lib/tinyxml/tinyxmlparser.cpp

${OBJECTDIR}/Gui/moc_MappingToolWindow.o: Gui/moc_MappingToolWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/Gui
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Gui/moc_MappingToolWindow.o Gui/moc_MappingToolWindow.cpp

${OBJECTDIR}/IrrWorker.o: IrrWorker.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/IrrWorker.o IrrWorker.cpp

${OBJECTDIR}/_ext/2033245622/ZwoptexParser.o: ../Game/Src/ZwoptexParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/ZwoptexParser.o ../Game/Src/ZwoptexParser.cpp

${OBJECTDIR}/_ext/1676536254/tinyxml.o: ../lib/tinyxml/tinyxml.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1676536254
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1676536254/tinyxml.o ../lib/tinyxml/tinyxml.cpp

${OBJECTDIR}/Gui/MainWindow.o: Gui/MainWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/Gui
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Gui/MainWindow.o Gui/MainWindow.cpp

${OBJECTDIR}/_ext/2033245622/StaticGameObject.o: ../Game/Src/StaticGameObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/StaticGameObject.o ../Game/Src/StaticGameObject.cpp

${OBJECTDIR}/MapViewer.o: MapViewer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/MapViewer.o MapViewer.cpp

${OBJECTDIR}/_ext/2033245622/Sprite.o: ../Game/Src/Sprite.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/Sprite.o ../Game/Src/Sprite.cpp

${OBJECTDIR}/_ext/2033245622/MappingFile.o: ../Game/Src/MappingFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/MappingFile.o ../Game/Src/MappingFile.cpp

${OBJECTDIR}/Gui/moc_MainWindow.o: Gui/moc_MainWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/Gui
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Gui/moc_MainWindow.o Gui/moc_MainWindow.cpp

${OBJECTDIR}/_ext/2033245622/Page.o: ../Game/Src/Page.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/Page.o ../Game/Src/Page.cpp

${OBJECTDIR}/Gui/QIrrControl.o: Gui/QIrrControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/Gui
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Gui/QIrrControl.o Gui/QIrrControl.cpp

${OBJECTDIR}/MappingToolWindowController.o: MappingToolWindowController.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/MappingToolWindowController.o MappingToolWindowController.cpp

${OBJECTDIR}/_ext/2033245622/AssetsManager.o: ../Game/Src/AssetsManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/AssetsManager.o ../Game/Src/AssetsManager.cpp

${OBJECTDIR}/_ext/2033245622/LevelManager.o: ../Game/Src/LevelManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/LevelManager.o ../Game/Src/LevelManager.cpp

${OBJECTDIR}/MainWindowController.o: MainWindowController.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/MainWindowController.o MainWindowController.cpp

${OBJECTDIR}/_ext/2033245622/AnimatedGameObject.o: ../Game/Src/AnimatedGameObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/AnimatedGameObject.o ../Game/Src/AnimatedGameObject.cpp

${OBJECTDIR}/Gui/moc_AboutWindow.o: Gui/moc_AboutWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/Gui
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Gui/moc_AboutWindow.o Gui/moc_AboutWindow.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/qteditor

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
