/*
 * File:   EdApp.cpp
 * Author: Timur Losev aka void
 * Email: timur.losev@gmail.com
 * Created on February 6, 2012, 12:46 AM
 */

#include "EdApp.h"
#include "EdPresenterHolder.h"
#include "EdViewHolder.h"
#include "EdControlHolder.h"
#include "CLogger.h"

//Game classes
#include "AssetsManager.h"

IMPLEMENT_APP(EdApp);

#ifdef WIN32
extern void RedirectIOToConsole();
#endif

static CLogger* logger = NULL;
static EdViewHolder* vholder = NULL;
static EdPresenterHolder* pholder = NULL;
static EdControlHolder* cholder = NULL;
static AssetsManager* astsmagr = NULL;

bool EdApp::OnInit()
{
#ifdef WIN32
    RedirectIOToConsole();
#endif

    //wxInitAllImageHandlers();
    logger = new CLogger();
    LOGGER->Initialize("Editor", "Editor Log");
    vholder = new EdViewHolder();
    pholder = new EdPresenterHolder();
    cholder = new EdControlHolder();
    astsmagr = new AssetsManager();

    EdPresenterHolder::getRef().CreateGui();
    EdPresenterHolder::getRef().ShowMainWindow();
    return true;
}

EdApp::~EdApp()
{
    LogDebug("Going down.");
    APP_API_DEL(astsmagr);
    APP_API_DEL(cholder);
    APP_API_DEL(pholder);
    APP_API_DEL(cholder);
    APP_API_DEL(astsmagr);
}