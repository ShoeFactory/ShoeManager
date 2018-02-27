#include <QCoreApplication>
#include "ShoeCommandExecutor.hpp"
#include "logger.h"

int main(int argc, char *argv[])
{
    Logger::instance()->init ();
    Logger::instance()->debug("Hello World");

    QCoreApplication a(argc, argv);

    ShoeCommandExecutor executor;

    if(executor.initServer())
        qDebug() << "init succeed";
    else
        qDebug() << "init failed";

    return a.exec();
}
