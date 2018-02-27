#include "AccountLoginWidget.hpp"
#include "ShoeManagerNetwork.hpp"
#include "ShoeManagerNetworkConfig.hpp"
#include <QDebug>

AccountLoginWidget::AccountLoginWidget(QWidget *parent) : QWidget(parent)
{
    initLayout();
    initConnection();


    mLineTelephone->setText("18710944280");
    mLinePasswd->setText("'''");
}

void AccountLoginWidget::loginButtonClicked()
{
    auto result = ShoeManagerNetwork::getInstance()->login(mLineTelephone->text(), mLinePasswd->text());
    if(result->oReturnCode == 0)
    {
        // 登录成功 获得token
        auto object = result->oReturnData.toObject();
        auto token = object["token"].toString();
        ShoeManagerNetworkConfig::getInstance()->setToken(token);

        emit loginSucceed();
    }
    else
    {
        qDebug() << result->oReturnMessage;
    }
}

void AccountLoginWidget::initLayout()
{
    mLabelTelephone = new QLabel("账号");
    mLabelPasswd = new QLabel("密码");
    mLineTelephone = new QLineEdit;
    mLinePasswd = new QLineEdit;

    mLabelPrompt = new QLabel;

    mButtonLogin = new QPushButton("登录");
    mButtonRegister = new QPushButton("立即注册");
    mButtonPasswd = new QPushButton("找回密码");

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(mLabelTelephone, mLineTelephone);
    formLayout->addRow(mLabelPasswd, mLinePasswd);

    QHBoxLayout *promptLayout = new QHBoxLayout;
    promptLayout->addWidget(mLabelPrompt);

    QHBoxLayout *loginLayout = new QHBoxLayout;
    loginLayout->addWidget(mButtonLogin);

    QHBoxLayout *otherLayout = new QHBoxLayout;
    otherLayout->addWidget(mButtonRegister);
    otherLayout->addStretch(1);
    otherLayout->addWidget(mButtonPasswd);

    QVBoxLayout *vboxMain = new QVBoxLayout(this);
    vboxMain->addLayout(formLayout);
    vboxMain->addLayout(loginLayout);
    vboxMain->addLayout(otherLayout);
}

void AccountLoginWidget::initConnection()
{
    connect(mButtonRegister, &QPushButton::clicked, this, &AccountLoginWidget::gotoRegister);
    connect(mButtonPasswd, &QPushButton::clicked, this, &AccountLoginWidget::gotoPasswd);

    connect(mButtonLogin, &QPushButton::clicked, this, &AccountLoginWidget::loginButtonClicked);
}

