#include "AccountEditorUI.hpp"
#include "IconFont.hpp"
#include <QCoreApplication>

AccountEditorUI::AccountEditorUI(QWidget *parent)
    : QUtilsFramelessDialog(parent)
{
    initLayout();
    initConnection();
}

void AccountEditorUI::setCurrentWidget(AccountEditorUI::UIID id)
{
    switch (id) {
    case Account_login:
        mStacked->setCurrentWidget(mLogin);
        mButtonReturnToLogin->setVisible(false);
        break;
    case Account_passwd:
        mStacked->setCurrentWidget(mPasswd);
        mButtonReturnToLogin->setVisible(true);
        break;
    case Account_register:
        mStacked->setCurrentWidget(mRegister);
        mButtonReturnToLogin->setVisible(true);
        break;
    default:
        break;
    }
}

void AccountEditorUI::initLayout()
{

    QHBoxLayout *hboxTitleToolBar = new QHBoxLayout;
    {
        mButtonReturnToLogin = new QPushButton(QString(QChar(IconFont::Left)));
        hboxTitleToolBar->addWidget(mButtonReturnToLogin);
        hboxTitleToolBar->setMargin(0);
        this->setTitleToolBarLayout(hboxTitleToolBar);

        mButtonReturnToLogin->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        mButtonReturnToLogin->setFont(IconFont::getInstance()->font());
        mButtonReturnToLogin->setFocusPolicy(Qt::NoFocus);
        mButtonReturnToLogin->setFixedWidth(23);
        mButtonReturnToLogin->setStyleSheet("QPushButton{"
                              "color : white;"
                              "border: 0px;"
                              "}"
                              "QPushButton:hover{"
                              "background-color: rgb(255, 0, 0)"
                              "}");
    }

    mLogin = new AccountLoginWidget;
    mPasswd = new AccountPasswdWidget;
    mRegister = new AccountRegisterWidget;

    mStacked = new QStackedWidget;
    mStacked->addWidget(mLogin);
    mStacked->addWidget(mPasswd);
    mStacked->addWidget(mRegister);

    QHBoxLayout *hboxLayoutEditUI = new QHBoxLayout;

    QWidget *widgetEditUI = new QWidget;
    {
        QVBoxLayout *vbox = new QVBoxLayout;
        vbox->addStretch(4);
        vbox->addWidget(mStacked);
        vbox->addStretch(5);
        hboxLayoutEditUI->addSpacing(280);
        hboxLayoutEditUI->addLayout(vbox);
        hboxLayoutEditUI->addSpacing(80);
    }

    hboxLayoutEditUI->addWidget(widgetEditUI);
    this->setBodyLayout(hboxLayoutEditUI);

    setCurrentWidget(Account_login);
    setTitleText("消防员定位监测系统");
    setFixedSize(600,400);

    this->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = this->palette();
    QString loginpng = qApp->applicationDirPath() + "/login.png";
    palette.setBrush(QPalette::Window, QBrush(QPixmap(loginpng)));
    this->setPalette(palette);
}

void AccountEditorUI::initConnection()
{
    connect(mLogin, &AccountLoginWidget::gotoPasswd, [=](){
       setCurrentWidget(Account_passwd);
    });
    connect(mLogin, &AccountLoginWidget::gotoRegister, [=](){
        setCurrentWidget(Account_register);
    });
    connect(mLogin, &AccountLoginWidget::loginSucceed, [=](){
        this->accept();
    });

    connect(mButtonReturnToLogin, &QPushButton::clicked, [=](){
        setCurrentWidget(Account_login);
    });
}
