#include <QApplication>
#include <QtWebEngine>
#include <QSplashScreen>

#include "MainWidget.hpp"
#include "AccountEditorUI.hpp"


int main(int argc, char *argv[])
{
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "9223");
    QApplication a(argc, argv);
    QtWebEngine::initialize();

    QSplashScreen  splashWindow(QPixmap(qApp->applicationDirPath() + "/splash.png"));
    splashWindow.show();

    QFile file(a.applicationDirPath() + "/style/black.qss");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());
    file.close();


    AccountEditorUI login;
    MainWidget *w = new MainWidget;

    for(int i=0; i<4; i++)
    {
       QThread::msleep(500);
       qApp->processEvents();
    }

    splashWindow.close();

    if(login.exec() == QDialog::Accepted)
    {
        w->showMaximized();
        return a.exec();
    }
    else
    {
        return 0;
    }
}
