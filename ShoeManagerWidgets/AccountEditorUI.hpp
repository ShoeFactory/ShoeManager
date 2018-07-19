#ifndef ACCOUNTEDITOR_HPP
#define ACCOUNTEDITOR_HPP

#include "shoemanagerwidgets_global.h"
#include <QLineEdit>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QStackedWidget>

#include "QUtilsFramelessDialog.hpp"
#include "AccountLoginWidget.hpp"
#include "AccountPasswdWidget.hpp"
#include "AccountRegisterWidget.hpp"

class SHOEMANAGERWIDGETSSHARED_EXPORT AccountEditorUI : public QUtilsFramelessDialog
{
public:
    enum UIID{
        Account_login = 0,
        Account_passwd,
        Account_register,
    };

public:
    AccountEditorUI(QWidget *parent=nullptr);
    void setCurrentWidget(UIID id);

private:
    void initLayout();
    void initConnection();

private:
    AccountLoginWidget *mLogin;
    AccountPasswdWidget *mPasswd;
    AccountRegisterWidget *mRegister;
    QStackedWidget *mStacked;

    QPushButton *mButtonReturnToLogin;
};

#endif // ACCOUNTEDITOR_HPP
