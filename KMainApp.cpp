/*
 * Copyright by yosh from Ke.mu Studio 2013
 * Contact y@ke.mu for questions
 */

#include <QtGui/QGuiApplication>
#include <QtWebKit>
#include <QWebFrame>
#include <QtWidgets>
#include <QWebView>

#include "kmainwindow.h"

//#define KDEBUG_ALL_ON
#include "KDebug.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /* init main window */
    KMainWindow mainWindow;
    mainWindow.resize(400, 300);
    mainWindow.show();
    mainWindow.setWindowTitle(QApplication::translate("toplevel", "Ke.mu Studio - GMail auto-clicker"));

    return app.exec();
}
