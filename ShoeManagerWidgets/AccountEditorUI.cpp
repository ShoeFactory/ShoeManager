#include "AccountEditorUI.hpp"
#include "IconFont.hpp"

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

    mStacked = new QStackedLayout;
    mStacked->addWidget(mLogin);
    mStacked->addWidget(mPasswd);
    mStacked->addWidget(mRegister);

    this->setBodyLayout(mStacked);

    setCurrentWidget(Account_login);
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
