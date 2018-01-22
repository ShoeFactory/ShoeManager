#include "AccountPasswdWidget.hpp"
#include "ShoeManagerNetwork.hpp"
#include "ShoeManagerNetworkResult.hpp"
#include <QDebug>

AccountPasswdWidget::AccountPasswdWidget(QWidget *parent) : QWidget(parent)
{
    initLayout();
    initConnection();
}

void AccountPasswdWidget::buttonValidateClicked()
{
    auto result = ShoeManagerNetwork::getInstance()->passwdQRCode(mLineTelephone->text());
    if(result->oReturnCode == 0)
    {

    }
    else
    {
        qDebug() << result->oReturnMessage;
    }
}

void AccountPasswdWidget::buttonUpdatePasswordClicked()
{
    auto result = ShoeManagerNetwork::getInstance()->passwdRetrive(
                mLineTelephone->text(), mLinePasswd->text(), mlineValidate->text());

    if(result->oReturnCode == 0)
    {

    }
    else
    {
        qDebug() << result->oReturnMessage;
    }
}

void AccountPasswdWidget::initLayout()
{
    mLabelTelephone = new QLabel("账号");
    mLabelValidate = new QLabel("验证码");
    mLabelPasswd = new QLabel("新密码");
    mLabelPasswdConfirm = new QLabel("确认密码");
    mlineValidate = new QLineEdit;
    mLineTelephone = new QLineEdit;
    mLinePasswd = new QLineEdit;
    mLinePasswdConfirm = new QLineEdit;

    mLabelPrompt = new QLabel;

    mButtonValidate = new QPushButton("获取验证码");
    mButtonPasswd = new QPushButton("找回密码");

    QHBoxLayout *hboxValidate = new QHBoxLayout;
    hboxValidate->addWidget(mlineValidate);
    hboxValidate->addWidget(mButtonValidate);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(mLabelTelephone, mLineTelephone);
    formLayout->addRow(mLabelValidate, hboxValidate);
    formLayout->addRow(mLabelPasswd, mLinePasswd);
    formLayout->addRow(mLabelPasswdConfirm, mLinePasswdConfirm);

    QHBoxLayout *promptLayout = new QHBoxLayout;
    promptLayout->addWidget(mLabelPrompt);

    QHBoxLayout *passwdLayout = new QHBoxLayout;
    passwdLayout->addWidget(mButtonPasswd);

    QVBoxLayout *vboxMain = new QVBoxLayout(this);
    vboxMain->addLayout(formLayout);
    vboxMain->addLayout(passwdLayout);
}

void AccountPasswdWidget::initConnection()
{
    connect(mButtonValidate, &QPushButton::clicked, this, &AccountPasswdWidget::buttonValidateClicked);
    connect(mButtonPasswd, &QPushButton::clicked, this, &AccountPasswdWidget::buttonUpdatePasswordClicked);
}
