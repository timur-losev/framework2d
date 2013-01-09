/*
 * File:   main.cpp
 * Author: void
 *
 * Created on September 21, 2012, 3:00 PM
 */

#include <cstdlib>


#include "MainWindow.h"
#include <QtGui/QApplication>
using namespace std;

/*
 *
 */
int main(int argc, char** argv)
{

    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}

