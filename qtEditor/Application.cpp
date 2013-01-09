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
#include "EditFrameController.h"
#include "IRegularView.h"

//#include "Sigslot2.h"

#include "AssetsManager.h"

/*#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>*/

//#include "SigSlot2Test.h"
/*
 *
 */
int main(int argc, char** argv)
{

    /* QApplication app(argc, argv);
  QWidget *test = new QWidget;
  QScrollArea area(0);
  area.setWidget(test); // A
  area.setWidgetResizable(true);
  QGridLayout gl(test);
  gl.setSpacing(0);
  gl.setMargin(0);
  QPushButton b0("1", test);
  gl.addWidget(&b0,0,0);
  QPushButton b1("2", test);
  gl.addWidget(&b1,0,1);
  QPushButton b2("3", test);
  gl.addWidget(&b2,1,0);
  QPushButton b3("4", test);
  gl.addWidget(&b3,1,1);
  QPushButton b4("5", test);
  gl.addWidget(&b4,2,0);
  QPushButton b5("6", test);
  gl.addWidget(&b5,2,1);
  area.show();
  return app.exec();*/

    QApplication app(argc, argv);

    Common::Logger* logger = new Common::Logger();
    logger->Initialize("qtEditor", "debug");

    GuiManager* guimanager = new GuiManager();
    guimanager->CreateGui();

    MainWindowControllerPtr mainWnd = GuiManager::getRef().CreateMainWindow();
    mainWnd->View().ShowView();

    EditFrameControllerPtr editFrame = GuiManager::getRef().CreateEditFrame();
    mainWnd->SetEditFrame(editFrame);

    AssetsManager* assetmanager = new AssetsManager();

    int ret = app.exec();

    APP_API_DEL(assetmanager);
    APP_API_DEL(guimanager);
    APP_API_DEL(logger);
    return ret;
}

