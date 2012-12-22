#
# File			make_platform.mak
# Title			Platform specific makefile
# Author		PowerVR
#
# Copyright		Copyright 2003-2004 by Imagination Technologies Limited.
#

ifdef TOOLCHAIN
	PLAT_CC  = $(TOOLCHAIN)/bin/$(CROSS_COMPILE)gcc
	PLAT_CPP = $(TOOLCHAIN)/bin/$(CROSS_COMPILE)g++
	PLAT_AR  = $(TOOLCHAIN)/bin/$(CROSS_COMPILE)ar
else
	PLAT_CC  = $(CROSS_COMPILE)gcc
	PLAT_CPP = $(CROSS_COMPILE)g++
	PLAT_AR  = $(CROSS_COMPILE)ar
endif

ifndef X11ROOT
X11ROOT  = /usr/X11R6
endif

ifeq "$(X11BUILD)" "1"
ifndef X11ROOT
$(error When building an X11 BUILD you must set X11ROOT to point at the location where your X11 headers and libs can be found.)
endif
ifeq "$(EWSBUILD)" "1"
$(error Cannot have both X11BUILD and EWSBUILD enabled at the same time)
endif
WS_LIBS = -L$(X11ROOT)/lib -lX11 -lXau
WS_INC  = $(X11ROOT)/include
WS = X11
else
ifeq "$(EWSBUILD)" "1"
PLAT_CFLAGS = -DEWS
WS_LIBS = -lews
WS_INC =
WS=EWS
else
WS_LIBS =
WS_INC  =
WS = Raw
endif
endif

LIBDIR ?= $(SDKDIR)/Builds/OGLES/$(PLATFORM)/Lib
LIBDIR_FLAGS = -L$(LIBDIR) -Wl,--rpath-link,$(LIBDIR)

ifdef Debug
DEBUG_RELEASE = Debug
PLAT_CFLAGS   += -m32 -DBUILD_OGLES -Wall -DDEBUG -g -march=i686
else
DEBUG_RELEASE = Release
PLAT_CFLAGS   += -m32 -DBUILD_OGLES -Wall -DRELEASE -O2 -march=i686
endif

ifdef SDKDIR
SDKDIR   := $(shell cd $(SDKDIR) && pwd)
PLAT_INC  = $(SDKDIR)/Builds/OGLES/Include \
			$(WS_INC)
endif

PLAT_OBJPATH = ../$(PLATFORM)/$(DEBUG_RELEASE)$(WS)
PLAT_LINK = $(LIBDIR_FLAGS) -lGLES_CM $(WS_LIBS)

