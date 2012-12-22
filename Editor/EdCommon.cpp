#include "EdCommon.h"

//irr::video::IVideoDriver* g_Driver = NULL;

std::stack<DriverPtr> G::DriverStack;
std::stack<DebugFontPtr> G::FontStack;