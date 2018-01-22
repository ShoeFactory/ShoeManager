#ifndef QUTILSFRAMLESSMESSAGEBOX_HPP
#define QUTILSFRAMLESSMESSAGEBOX_HPP

#include <QObject>
#include "shoemanagercore_global.h"

class SHOEMANAGERCORESHARED_EXPORT QUtilsFramLessMessageBox : public QObject
{
    Q_OBJECT
public:    
    QUtilsFramLessMessageBox(QObject *parent=nullptr);

    static void info(QString content, QString title = QString("提示"));
    static bool confirm(QString content, QString title = QString("提示"));
};

#endif // QUTILSFRAMLESSMESSAGEBOX_HPP
