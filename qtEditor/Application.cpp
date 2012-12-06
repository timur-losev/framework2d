/*
 * File:   main.cpp
 * Author: void
 *
 * Created on September 22, 2012, 8:29 PM
 */


#include <QtGui/QApplication>

#include "EdPrec.h"
#include "GuiManager.h"

#include "MainWindowController.h"
#include "IRegularView.h"

//#include "Sigslot2.h"

#include "AssetsManager.h"

using namespace std;


std::stack<DebugFontPtr> G::FontStack;
/*
 *
 */
int main(int argc, char** argv)
{
    QApplication app(argc, argv);


    Common::Logger* logger = new Common::Logger();
    logger->Initialize("qtEditor", "debug");

    GuiManager* guimanager = new GuiManager();
    guimanager->CreateGui();

    MainWindowControllerPtr mainWnd = GuiManager::getRef().CreateMainWindow();
    mainWnd->View().ShowView();

	AssetsManager* assetmanager = new AssetsManager();

    int ret = app.exec();

    APP_API_DEL(guimanager);
    APP_API_DEL(logger);
    return ret;
}

