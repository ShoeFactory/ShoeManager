#include <QApplication>
#include <QtWebEngine>
#include "MainWidget.hpp"
#include "AccountEditorUI.hpp"


int main(int argc, char *argv[])
{
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "9223");
    QApplication a(argc, argv);
    QtWebEngine::initialize();

//    QFile file(a.applicationDirPath() + "/style/black.qss");
//    file.open(QFile::ReadOnly);
//    a.setStyleSheet(file.readAll());
//    file.close();

    AccountEditorUI login;
    MainWidget *w = new MainWidget;

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
