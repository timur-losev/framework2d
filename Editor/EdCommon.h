/*
 * File:   EdCommon.h
 * Author: void
 *
 * Created on February 3, 2012, 11:28 PM
 */

#ifndef EDCOMMON_H
#    define	EDCOMMON_H

#include "boost/signals.hpp"
#include "boost/bind.hpp"
#include "boost/signal.hpp"

#include "EdPrec.h"

enum CursorTypes
{
	CURSOR_DEFAULT = 0,
	CURSOR_SELECT,
	CURSOR_MOVE,
	CURSOR_HAND,
	CURSORS_COUNT
};

#endif	/* EDCOMMON_H */

