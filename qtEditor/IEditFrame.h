/*
 * File:   IEditFrame.h
 * Author: void
 *
 * Created on December 18, 2012, 23:29
 */

#pragma once

#include "IRegularView.h"

class IEditFrame: public IRegularView
{
protected:

public:

    enum E_SIGNALS
    {
        ES_ON_ADD_EMPTY_OBJECT
    };
};