/*
 * File:   main.cpp
 * Author: void
 *
 * Created on September 22, 2012, 8:29 PM
 */

#include "EdPrec.h"
#include <QtGui/QApplication>
#include "GuiManager.h"

#include "MainWindowController.h"
#include "IRegularView.h"

//#include "Sigslot2.h"

#include "AssetsManager.h"

#include "SigSlot2Test.h"

std::stack<DebugFontPtr> G::FontStack;
/*
 *
 */
int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    Sigslot2Test::main();

    return 0;

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

