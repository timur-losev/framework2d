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
	${OBJECTDIR}/_ext/2033245622/EditablePagedLevel.o \
	${OBJECTDIR}/EdAtlasToolWndView.o \
	${OBJECTDIR}/_ext/2033245622/LevelFile.o \
	${OBJECTDIR}/_ext/2033245622/GameObject.o \
	${OBJECTDIR}/EdSetNameForSelectionPresenter.o \
	${OBJECTDIR}/EdPresenterHolder.o \
	${OBJECTDIR}/WxIrrControl.o \
	${OBJECTDIR}/_ext/1676536254/tinystr.o \
	${OBJECTDIR}/EdMappingToolWndView.o \
	${OBJECTDIR}/MappingToolLevel.o \
	${OBJECTDIR}/AnimViewer.o \
	${OBJECTDIR}/EdControlHolder.o \
	${OBJECTDIR}/_ext/2033245622/ILevel.o \
	${OBJECTDIR}/EdSetValuePresenter.o \
	${OBJECTDIR}/EdAtlasToolWndPresenter.o \
	${OBJECTDIR}/_ext/1676536254/tinyxmlerror.o \
	${OBJECTDIR}/AtlasToolLevel.o \
	${OBJECTDIR}/_ext/1676536254/tinyxmlparser.o \
	${OBJECTDIR}/IrrWorker.o \
	${OBJECTDIR}/_ext/2033245622/ZwoptexParser.o \
	${OBJECTDIR}/_ext/1676536254/tinyxml.o \
	${OBJECTDIR}/_ext/2033245622/StaticGameObject.o \
	${OBJECTDIR}/EdSetValueView.o \
	${OBJECTDIR}/MapViewer.o \
	${OBJECTDIR}/_ext/2033245622/Sprite.o \
	${OBJECTDIR}/_ext/2033245622/MappingFile.o \
	${OBJECTDIR}/_ext/2033245622/Page.o \
	${OBJECTDIR}/EdViewHolder.o \
	${OBJECTDIR}/EdMappingPresenter.o \
	${OBJECTDIR}/EdCommon.o \
	${OBJECTDIR}/EdApp.o \
	${OBJECTDIR}/_ext/2033245622/AssetsManager.o \
	${OBJECTDIR}/_ext/2033245622/LevelManager.o \
	${OBJECTDIR}/_ext/2033245622/AnimatedGameObject.o \
	${OBJECTDIR}/EdMainWndView.o \
	${OBJECTDIR}/EdMainWndPresenter.o \
	${OBJECTDIR}/EdSetNameForSelectionView.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/editor

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/editor: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/editor ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/2033245622/EditablePagedLevel.o: ../Game/Src/EditablePagedLevel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/EditablePagedLevel.o ../Game/Src/EditablePagedLevel.cpp

${OBJECTDIR}/EdAtlasToolWndView.o: EdAtlasToolWndView.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/EdAtlasToolWndView.o EdAtlasToolWndView.cpp

${OBJECTDIR}/_ext/2033245622/LevelFile.o: ../Game/Src/LevelFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/LevelFile.o ../Game/Src/LevelFile.cpp

${OBJECTDIR}/_ext/2033245622/GameObject.o: ../Game/Src/GameObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/GameObject.o ../Game/Src/GameObject.cpp

${OBJECTDIR}/EdSetNameForSelectionPresenter.o: EdSetNameForSelectionPresenter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/EdSetNameForSelectionPresenter.o EdSetNameForSelectionPresenter.cpp

${OBJECTDIR}/EdPresenterHolder.o: EdPresenterHolder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/EdPresenterHolder.o EdPresenterHolder.cpp

${OBJECTDIR}/WxIrrControl.o: WxIrrControl.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/WxIrrControl.o WxIrrControl.cpp

${OBJECTDIR}/_ext/1676536254/tinystr.o: ../lib/tinyxml/tinystr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1676536254
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1676536254/tinystr.o ../lib/tinyxml/tinystr.cpp

${OBJECTDIR}/EdMappingToolWndView.o: EdMappingToolWndView.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/EdMappingToolWndView.o EdMappingToolWndView.cpp

${OBJECTDIR}/MappingToolLevel.o: MappingToolLevel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/MappingToolLevel.o MappingToolLevel.cpp

${OBJECTDIR}/AnimViewer.o: AnimViewer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/AnimViewer.o AnimViewer.cpp

${OBJECTDIR}/EdControlHolder.o: EdControlHolder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/EdControlHolder.o EdControlHolder.cpp

${OBJECTDIR}/_ext/2033245622/ILevel.o: ../Game/Src/ILevel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/ILevel.o ../Game/Src/ILevel.cpp

${OBJECTDIR}/EdSetValuePresenter.o: EdSetValuePresenter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/EdSetValuePresenter.o EdSetValuePresenter.cpp

${OBJECTDIR}/EdAtlasToolWndPresenter.o: EdAtlasToolWndPresenter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/EdAtlasToolWndPresenter.o EdAtlasToolWndPresenter.cpp

${OBJECTDIR}/_ext/1676536254/tinyxmlerror.o: ../lib/tinyxml/tinyxmlerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1676536254
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1676536254/tinyxmlerror.o ../lib/tinyxml/tinyxmlerror.cpp

${OBJECTDIR}/AtlasToolLevel.o: AtlasToolLevel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/AtlasToolLevel.o AtlasToolLevel.cpp

${OBJECTDIR}/_ext/1676536254/tinyxmlparser.o: ../lib/tinyxml/tinyxmlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1676536254
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1676536254/tinyxmlparser.o ../lib/tinyxml/tinyxmlparser.cpp

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

${OBJECTDIR}/_ext/2033245622/StaticGameObject.o: ../Game/Src/StaticGameObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/StaticGameObject.o ../Game/Src/StaticGameObject.cpp

${OBJECTDIR}/EdSetValueView.o: EdSetValueView.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/EdSetValueView.o EdSetValueView.cpp

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

${OBJECTDIR}/_ext/2033245622/Page.o: ../Game/Src/Page.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/Page.o ../Game/Src/Page.cpp

${OBJECTDIR}/EdViewHolder.o: EdViewHolder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/EdViewHolder.o EdViewHolder.cpp

${OBJECTDIR}/EdMappingPresenter.o: EdMappingPresenter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/EdMappingPresenter.o EdMappingPresenter.cpp

${OBJECTDIR}/EdCommon.o: EdCommon.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/EdCommon.o EdCommon.cpp

${OBJECTDIR}/EdApp.o: EdApp.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/EdApp.o EdApp.cpp

${OBJECTDIR}/_ext/2033245622/AssetsManager.o: ../Game/Src/AssetsManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/AssetsManager.o ../Game/Src/AssetsManager.cpp

${OBJECTDIR}/_ext/2033245622/LevelManager.o: ../Game/Src/LevelManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/LevelManager.o ../Game/Src/LevelManager.cpp

${OBJECTDIR}/_ext/2033245622/AnimatedGameObject.o: ../Game/Src/AnimatedGameObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2033245622
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2033245622/AnimatedGameObject.o ../Game/Src/AnimatedGameObject.cpp

${OBJECTDIR}/EdMainWndView.o: EdMainWndView.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/EdMainWndView.o EdMainWndView.cpp

${OBJECTDIR}/EdMainWndPresenter.o: EdMainWndPresenter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/EdMainWndPresenter.o EdMainWndPresenter.cpp

${OBJECTDIR}/EdSetNameForSelectionView.o: EdSetNameForSelectionView.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/EdSetNameForSelectionView.o EdSetNameForSelectionView.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/editor

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
