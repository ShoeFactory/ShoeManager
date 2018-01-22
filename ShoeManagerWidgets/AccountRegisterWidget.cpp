#include "AccountRegisterWidget.hpp"
#include "ShoeManagerNetworkResult.hpp"
#include "ShoeManagerNetwork.hpp"
#include <QDebug>

AccountRegisterWidget::AccountRegisterWidget(QWidget *parent) : QWidget(parent)
{
    initLayout();
    initConnection();
}

void AccountRegisterWidget::registerValidateClicked()
{
    auto result = ShoeManagerNetwork::getInstance()->registerQRCode(mLineTelephone->text());
    if(result->oReturnCode == 0)
    {

    }
    else
    {
        qDebug() << result->oReturnMessage;
    }
}

void AccountRegisterWidget::registerClicked()
{
    auto result = ShoeManagerNetwork::getInstance()->registerAccount(mLineTelephone->text(),
                                                                     mLinePasswd->text(),
                                                                     mlineValidate->text(),
                                                                     mLineName->text());
    if(result->oReturnCode == 0)
    {

    }
    else
    {
        qDebug() << result->oReturnMessage;
    }
}

void AccountRegisterWidget::initLayout()
{
    mLabelTelephone = new QLabel("账号");
    mLabelValidate = new QLabel("验证码");
    mLabelPasswd = new QLabel("密码");
    mLabelPasswdConfirm = new QLabel("确认密码");
    mLabelName = new QLabel("用户名");
    mlineValidate = new QLineEdit;
    mLineTelephone = new QLineEdit;
    mLinePasswd = new QLineEdit;
    mLinePasswdConfirm = new QLineEdit;
    mLineName = new QLineEdit;

    mLabelPrompt = new QLabel;

    mButtonValidate = new QPushButton("获取验证码");
    mButtonRegister = new QPushButton("立即注册");

    QHBoxLayout *hboxValidate = new QHBoxLayout;
    hboxValidate->addWidget(mlineValidate);
    hboxValidate->addWidget(mButtonValidate);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(mLabelTelephone, mLineTelephone);
    formLayout->addRow(mLabelValidate, hboxValidate);
    formLayout->addRow(mLabelPasswd, mLinePasswd);
    formLayout->addRow(mLabelPasswdConfirm, mLinePasswdConfirm);
    formLayout->addRow(mLabelName, mLineName);

    QHBoxLayout *promptLayout = new QHBoxLayout;
    promptLayout->addWidget(mLabelPrompt);

    QHBoxLayout *registerLayout = new QHBoxLayout;
    registerLayout->addWidget(mButtonRegister);

    QVBoxLayout *vboxMain = new QVBoxLayout(this);
    vboxMain->addLayout(formLayout);
    vboxMain->addLayout(registerLayout);
}

void AccountRegisterWidget::initConnection()
{
    connect(mButtonValidate, &QPushButton::clicked, this, &AccountRegisterWidget::registerValidateClicked);
    connect(mButtonRegister, &QPushButton::clicked, this, &AccountRegisterWidget::registerClicked);
}
